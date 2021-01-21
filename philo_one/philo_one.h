/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:10:35 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/21 00:45:29 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct		s_parameters
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	struct timeval	bgn;
}					t_parameters;
t_parameters		g_param;

typedef struct		s_fork
{
	pthread_mutex_t	mutex;
	int				status;
}					t_fork;
t_fork				*g_fork;

typedef struct		s_thread
{
	pthread_t		thd;
	int				status;
	char			*name;
	int				die;
	int				last_eat;
	int				eat;
}					t_thread;
t_thread			*g_thd;

typedef struct		s_print
{
	pthread_mutex_t	mutex;
	int				val;
}					t_print;
t_print				g_print;

/*
** main.c
*/
void				var_free(void);

/*
** utils.c
*/
void				ft_usleep(int wait);
void				ft_putstr_fd(char *s, int fd);
char				*ft_itoa(int n);
int					ft_atoi(const char *nptr);

/*
** init.c
*/
void				thd_join(void);
int					thd_create(void);
void				init_malloc(void);
int					init_param(int argc, char *argv[]);

/*
** thread.c
*/
void				sleep_n_thinking(char *philo_name);
int					eating(int fork1, int fork2, char *philo_name);
int					is_die(int fork1, int fork2, char *philo_name);
int					get_fork(int fork1, int fork2, char *philo_name);
void				*thread_func(void	*philo_name);

/*
** thread_utils.c
*/
int					must_eat_cnt(void);
int					cal_timeval(struct timeval bgn);
void				print_sentence(char *philo_name, char *sentence);

/*
** get_mutex.c
*/
void				unlock_mutex(int *status, pthread_mutex_t *mutex);
void				get_fork_mutex(int fork, char *philo_name);
void				get_print_mutex(void);

#endif
