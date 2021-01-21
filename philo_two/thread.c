/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 00:48:27 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/21 15:11:22 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		is_die(int fork1, int fork2, char *philo_name)
{
	if ((cal_timeval(g_param.bgn) - g_thd[fork1].last_eat)
			> g_param.time_to_die)
	{

	}
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
		get_sem(fork2, philo_name);
		get_sem(fork1, philo_name);
	}
	else
	{
		get_sem(fork1, philo_name);
		get_sem(fork2, philo_name);
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
	}
	return (0);
}
