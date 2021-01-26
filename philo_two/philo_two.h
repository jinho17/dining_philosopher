/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 00:20:32 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/26 18:31:47 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <sys/types.h>

# define SEM_FORK "/philo_two_fork"
# define SEM_PT "/philo_two_print"

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

typedef struct		s_thread
{
	pthread_t		thd;
	char			*name;
	int				die;
	int				eat;
	int				last_eat;
}					t_thread;
t_thread			*g_thd;

typedef struct		s_semaphore
{
	sem_t			*fork;
	sem_t			*print;
}					t_semaphore;
t_semaphore			g_sem;

int					*g_fork;
int					g_print;

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
sem_t				*init_semaphore(char *name, int value);
void				init_malloc(void);
int					init_param(int argc, char *argv[]);

/*
** thread.c
*/
void				*thread_func(void	*philo_name);

/*
** thread_utils.c
*/
int					must_eat_cnt(void);
int					cal_timeval(struct timeval bgn);
void				print_sentence(char *philo_name, char *sentence);

/*
** semaphore.c
*/
void				get_sem_print(char *philo_name, char *str);
void				get_sem_fork(int fork, char *philo_name);

#endif
