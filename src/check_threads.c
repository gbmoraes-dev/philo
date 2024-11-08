/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoraes <gamoraes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:40:25 by gamoraes          #+#    #+#             */
/*   Updated: 2024/10/23 22:50:07 by gamoraes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	increase_long(t_mtx *mutex, long *value)
{
	mutex_handle(mutex, LOCK);
	(*value)++;
	mutex_handle(mutex, UNLOCK);
}

bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	unsync(t_philo *philo)
{
	if (philo->table->nb_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_thr_ready))
		;
}
