/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:46:50 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/27 23:59:42 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define SEM_FORK "/philo_three_fork"
# define SEM_PT "/philo_three_print"
# define SEM_EAT "/philo_three_eat"

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

typedef struct		s_ps
{
	pid_t			*pid;
	char			**name;
	int				eat;
	int				last_eat;
}					t_ps;
t_ps				g_ps;

typedef struct		s_semaphore
{
	sem_t			*eat;
	sem_t			*fork;
	sem_t			*print;
}					t_semaphore;
t_semaphore			g_sem;

/*
** main.c
*/
void				var_free(void);

/*
** init.c
*/
void				ps_wait(void);
int					ps_create(void);
sem_t				*init_semaphore(char *name, int value);
void				init_malloc(void);
int					init_param(int argc, char *argv[]);

/*
** child_ps.c
*/
void				sleep_n_thinking(char *philo_name);
void				eating(char *philo_name);
void				is_die(char *philo_name);
void				get_fork(char *philo_name);
void				child_ps(char *philo_name);

/*
** child_ps_utils.c
*/
int					cal_timeval(struct timeval bgn);
void				print_sentence(char *philo_name, char *sentence);

/*
** utils.c
*/
void				ft_usleep(int wait);
void				ft_putstr_fd(char *s, int fd);
char				*ft_itoa(int n);
int					ft_atoi(const char *nptr);

#endif
