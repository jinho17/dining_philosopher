/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 00:48:27 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/26 18:30:47 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	sleep_n_thinking(char *philo_name)
{
	get_sem_print(philo_name, " is sleeping\n");
	ft_usleep(g_param.time_to_sleep);
	get_sem_print(philo_name, " is thinking\n");
}

int		eating(int fork1, int fork2, char *philo_name)
{
	get_sem_print(philo_name, " is eating\n");
	g_thd[fork1].eat++;
	g_thd[fork1].last_eat = cal_timeval(g_param.bgn);
	ft_usleep(g_param.time_to_eat);
	g_fork[fork1] = 0;
	g_fork[fork2] = 0;
	sem_post(g_sem.fork);
	sem_post(g_sem.fork);
	if (g_thd[fork1].eat == g_param.number_of_times_each_philosopher_must_eat)
	{
		while (must_eat_cnt() == 0)
			;
		return (-1);
	}
	return (0);
}

int		is_die(int fork1, int fork2, char *philo_name)
{
	if ((cal_timeval(g_param.bgn) - g_thd[fork1].last_eat)
			> g_param.time_to_die)
	{
		get_sem_print(philo_name, " died\n");
		g_thd[fork1].die = 1;
		g_fork[fork1] = 0;
		g_fork[fork2] = 0;
		sem_post(g_sem.fork);
		sem_post(g_sem.fork);
		return (1);
	}
	return (0);
}

int		get_fork(int fork1, int fork2, char *philo_name)
{
	int		idx;

	idx = 0;
	while (idx < g_param.number_of_philosophers)
	{
		if (g_thd[idx].die == 1)
			return (-1);
		idx++;
	}
	if (fork1 % 2 == 0)
	{
		get_sem_fork(fork2, philo_name);
		get_sem_fork(fork1, philo_name);
	}
	else
	{
		get_sem_fork(fork1, philo_name);
		get_sem_fork(fork2, philo_name);
	}
	return (0);
}

void	*thread_func(void *philo_name)
{
	int		fork1;
	int		fork2;

	fork1 = ft_atoi(philo_name) - 1;
	if (fork1 == g_param.number_of_philosophers - 1)
		fork2 = 0;
	else
		fork2 = fork1 + 1;
	while (1)
	{
		if (get_fork(fork1, fork2, philo_name) < 0)
			return (0);
		if (is_die(fork1, fork2, philo_name) > 0)
			return (0);
		if (eating(fork1, fork2, philo_name) < 0)
			return (0);
		sleep_n_thinking(philo_name);
	}
	return (0);
}
