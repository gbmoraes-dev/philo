/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoraes <gamoraes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:24:50 by gamoraes          #+#    #+#             */
/*   Updated: 2024/10/23 22:44:56 by gamoraes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (check_args(argc, argv))
		exit(EXIT_FAILURE);
	parsing(&table, argv);
	init_table(&table);
	dinner_start(&table);
	clean(&table);
}
