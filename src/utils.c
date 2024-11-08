/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoraes <gamoraes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:27:53 by gamoraes          #+#    #+#             */
/*   Updated: 2024/10/23 22:49:02 by gamoraes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	print_error(char *msg)
{
	printf(RED "%s" RST "\n", msg);
	exit(EXIT_FAILURE);
}

long	get_time(int time_code)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		print_error("Error when try to Gettimeofday");
	if (MILLISEC == time_code)
		return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
	else if (MICROSEC == time_code)
		return (time.tv_sec * 1e6 + time.tv_usec);
	else
		return (print_error("Wrong input to gettime"));
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed_time;
	long	remained;

	start = get_time(MICROSEC);
	while (get_time(MICROSEC) - start < usec)
	{
		if (end_simulation(table))
			break ;
		elapsed_time = get_time(MICROSEC) - start;
		remained = usec - elapsed_time;
		if (remained > 1e3)
			usleep(remained / 2);
		else
			while (get_time(MICROSEC) - start < usec)
				;
	}
}

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = get_time(MILLISEC) - philo->table->start_simulation;
	if (philo->full)
		return ;
	mutex_handle(&philo->table->write_mutex, LOCK);
	if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
		&& !end_simulation(philo->table))
		printf(W "%-6ld" RST " %d 🍽  \033[1;37mhas taken a fork\n", elapsed, philo->id);
	else if (EATING == status && !end_simulation(philo->table))
		printf(W "%-6ld" RST " %d 🍝 \033[1;33mis eating\033[0m\n" RST, elapsed, philo->id);
	else if (SLEEPING == status && !end_simulation(philo->table))
		printf(W "%-6ld" RST " %d 💤 \033[1;36mis sleeping\033[0m\n", elapsed, philo->id);
	else if (THINKING == status && !end_simulation(philo->table))
		printf(W "%-6ld" RST " %d 💡 \033[1;35mis thinking\033[0m\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED "%-6ld %d 💀 \033[1;31mdied\033[0m\n" RST, elapsed, philo->id);
	mutex_handle(&philo->table->write_mutex, UNLOCK);
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->nb_philos)
	{
		philo = table->philos + i;
		mutex_handle(&philo->philo_mutex, DESTROY);
	}
	mutex_handle(&table->write_mutex, DESTROY);
	mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}
