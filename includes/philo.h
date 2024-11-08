/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoraes <gamoraes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:38:26 by gamoraes          #+#    #+#             */
/*   Updated: 2024/11/08 00:03:25 by gamoraes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "../lib/libft/libft.h"
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef PHILO_MAX
#  define PHILO_MAX 200
# endif

# define RST "\033[0m"
# define RED "\033[0;31m"
# define W "\033[0;37m"

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	pthread_t			t_id;
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meal_time;
	t_fork				*left_fork;
	t_fork				*right_fork;
	t_mtx				philo_mutex;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	t_philo				*philos;
	t_fork				*forks;
	long				nb_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				must_eat;
	long				start_simulation;
	bool				end_simulation;
	bool				all_thr_ready;
	long				threads_running_nbr;
	pthread_t			monitor;
	t_mtx				table_mutex;
	t_mtx				write_mutex;

}						t_table;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	JOIN,
	DESTROY,
	CREATE,
	DETACH,
}						t_opcode;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}						t_philo_status;

// TIME
typedef enum e_time_code
{
	MILLISEC,
	MICROSEC,
}						t_time_code;

// VALIDATE AND PARSE

int						check_args(int argc, char **argv);
void					parsing(t_table *table, char **argv);
int						validation(char *argv);

// GET AND SET

void					set_long(t_mtx *mutex, long *dest, long value);
long					get_long(t_mtx *mutex, long *value);
bool					get_bool(t_mtx *mutex, bool *value);
void					set_bool(t_mtx *mutex, bool *dest, bool value);
bool					end_simulation(t_table *table);

// MUTEX AND THREADS HANDLE

void					mutex_handle(t_mtx *mutex, t_opcode op);
void					thread_handle(pthread_t *thread, void *(*foo)(void *),
							void *data, t_opcode op);

// INIT FUNCTIONS

void					init_table(t_table *table);

// DINNER

void					*one_philo(void *arg);
void					thinking(t_philo *philo, bool pre_simulation);
void					dinner_start(t_table *table);

// MONITOR

void					*monitor_dinner(void *data);

// CHECK THREADS

void					increase_long(t_mtx *mutex, long *value);
bool					all_threads_running(t_mtx *mutex, long *threads,
							long philo_nbr);
void					unsync(t_philo *philo);
void					wait_all_threads(t_table *table);

// UTILS

long					get_time(int time_code);
int						print_error(char *msg);
void					precise_usleep(long usec, t_table *table);
void					write_status(t_philo_status status, t_philo *philo);
void					clean(t_table *table);
bool					all_threads_running(t_mtx *mutex, long *threads,
							long philo_nbr);

#endif
