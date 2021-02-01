/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 00:48:27 by jinkim            #+#    #+#             */
/*   Updated: 2021/02/01 17:39:55 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	sleep_n_thinking(char *philo_name)
{
	print_sentence(philo_name, " is sleeping\n");
	ft_usleep(g_param.time_to_sleep);
	print_sentence(philo_name, " is thinking\n");
}

int		eating(int philo_num, char *philo_name)
{
	print_sentence(philo_name, " is eating\n");
	g_thd[philo_num].eat++;
	g_thd[philo_num].last_eat = cal_timeval(g_param.bgn);
	ft_usleep(g_param.time_to_eat);
	sem_post(g_sem.fork);
	sem_post(g_sem.fork);
	sem_post(g_sem.eat);
	if (g_thd[philo_num].eat
		== g_param.number_of_times_each_philosopher_must_eat
		&& g_param.number_of_times_each_philosopher_must_eat > 0)
	{
		g_enough_eat++;
		while (g_enough_eat != g_param.number_of_philosophers)
			;
		return (-1);
	}
	return (0);
}

int		is_die(int philo_num, char *philo_name)
{
	if ((cal_timeval(g_param.bgn) - g_thd[philo_num].last_eat)
			> g_param.time_to_die)
	{
		g_thd[philo_num].die = 1;
		print_sentence(philo_name, " died\n");
		sem_post(g_sem.fork);
		sem_post(g_sem.fork);
		sem_post(g_sem.eat);
		return (1);
	}
	return (0);
}

int		get_fork(char *philo_name)
{
	int		idx;

	idx = 0;
	while (idx < g_param.number_of_philosophers)
	{
		if (g_thd[idx].die == 1)
			return (-1);
		idx++;
	}
	sem_wait(g_sem.eat);
	sem_wait(g_sem.fork);
	print_sentence(philo_name, " has taken a fork\n");
	sem_wait(g_sem.fork);
	print_sentence(philo_name, " has taken a fork\n");
	return (0);
}

void	*thread_func(void *philo_name)
{
	int		philo_num;

	philo_num = ft_atoi(philo_name) - 1;
	while (1)
	{
		if (get_fork(philo_name) < 0)
			return (0);
		if (is_die(philo_num, philo_name) > 0)
			return (0);
		if (eating(philo_num, philo_name) < 0)
			return (0);
		sleep_n_thinking(philo_name);
	}
	return (0);
}
