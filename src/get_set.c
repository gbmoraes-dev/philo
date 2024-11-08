/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoraes <gamoraes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:27:40 by gamoraes          #+#    #+#             */
/*   Updated: 2024/10/23 22:51:39 by gamoraes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_bool(t_mtx *mutex, bool *dst, bool value)
{
	mutex_handle(mutex, LOCK);
	*dst = value;
	mutex_handle(mutex, UNLOCK);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	mutex_handle(mutex, LOCK);
	*dest = value;
	mutex_handle(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	mutex_handle(mutex, LOCK);
	ret = *value;
	mutex_handle(mutex, UNLOCK);
	return (ret);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	mutex_handle(mutex, LOCK);
	ret = *value;
	mutex_handle(mutex, UNLOCK);
	return (ret);
}

bool	end_simulation(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
