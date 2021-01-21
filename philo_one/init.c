/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 20:32:47 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/20 21:23:22 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	thd_join(void)
{
	int		idx;
	int		result;

	idx = 0;
	while (idx < g_param.number_of_philosophers)
	{
		pthread_join(g_thd[idx].thd, (void *)&result);
		idx++;
	}
}

int		thd_create(void)
{
	int		idx;
	int		rtn;

	idx = 0;
	while (idx < g_param.number_of_philosophers)
	{
		rtn = pthread_create(
				&g_thd[idx].thd, NULL, thread_func, (void *)g_thd[idx].name);
		if (rtn < 0)
			return (-1);
		idx++;
	}
	return (0);
}

void	init_malloc(void)
{
	int		idx;

	g_thd = (t_thread *)malloc(
				sizeof(t_thread) * g_param.number_of_philosophers);
	g_fork = (t_fork *)malloc(sizeof(t_fork) * g_param.number_of_philosophers);
	pthread_mutex_init(&g_print.mutex, NULL);
	g_print.val = 0;
	idx = 0;
	while (idx < g_param.number_of_philosophers)
	{
		g_thd[idx].status = 0;
		g_thd[idx].name = ft_itoa(idx + 1);
		g_thd[idx].die = 0;
		g_thd[idx].last_eat = 0;
		g_thd[idx].eat = 0;
		pthread_mutex_init(&g_fork[idx].mutex, NULL);
		g_fork[idx].status = 0;
		idx++;
	}
	gettimeofday(&g_param.bgn, NULL);
}

int		init_param(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (-1);
	g_param.number_of_philosophers = ft_atoi(argv[1]);
	g_param.time_to_die = ft_atoi(argv[2]);
	g_param.time_to_eat = ft_atoi(argv[3]);
	g_param.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		g_param.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		g_param.number_of_times_each_philosopher_must_eat = -1;
	if (g_param.number_of_philosophers < 2 || g_param.time_to_die < 0 ||
		g_param.time_to_eat < 0 || g_param.time_to_sleep < 0)
		return (-1);
	return (0);
}
