/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_ps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:09:01 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/27 23:38:28 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	sleep_n_thinking(char *philo_name)
{
	print_sentence(philo_name, " is sleeping\n");
	ft_usleep(g_param.time_to_sleep);
	print_sentence(philo_name, " is thinking\n");
}

void	eating(char *philo_name)
{
	print_sentence(philo_name, " is eating\n");
	g_ps.eat++;
	g_ps.last_eat = cal_timeval(g_param.bgn);
	ft_usleep(g_param.time_to_eat);
	sem_post(g_sem.fork);
	sem_post(g_sem.fork);
	sem_post(g_sem.eat);
	if (g_ps.eat == g_param.number_of_times_each_philosopher_must_eat &&
		g_param.number_of_times_each_philosopher_must_eat > 0)
		exit(0);
}

void	is_die(char *philo_name)
{
	if ((cal_timeval(g_param.bgn) - g_ps.last_eat) > g_param.time_to_die)
	{
		print_sentence(philo_name, " died\n");
		sem_post(g_sem.fork);
		sem_post(g_sem.fork);
		sem_post(g_sem.eat);
		exit(1);
	}
}

void	get_fork(char *philo_name)
{
	sem_wait(g_sem.eat);
	sem_wait(g_sem.fork);
	print_sentence(philo_name, " has taken a fork\n");
	sem_wait(g_sem.fork);
	print_sentence(philo_name, " has taken a fork\n");
}

void	child_ps(char *philo_name)
{
	while (1)
	{
		get_fork(philo_name);
		is_die(philo_name);
		eating(philo_name);
		sleep_n_thinking(philo_name);
	}
}
