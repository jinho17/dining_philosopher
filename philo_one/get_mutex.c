/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mutex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 20:43:55 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/20 19:49:51 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	unlock_mutex(int *status, pthread_mutex_t *mutex)
{
	*status = 0;
	pthread_mutex_unlock(mutex);
}

void	get_fork_mutex(int fork, char *philo_name)
{
	if (g_fork[fork].status == 0)
	{
		pthread_mutex_lock(&g_fork[fork].mutex);
		g_fork[fork].status = 1;
		get_print_mutex();
		print_sentence(philo_name, " has taken a fork\n");
		unlock_mutex(&g_print.val, &g_print.mutex);
	}
	else
	{
		while (g_fork[fork].status == 1)
			;
		get_fork_mutex(fork, philo_name);
	}
}

void	get_print_mutex(void)
{
	if (g_print.val == 0)
	{
		pthread_mutex_lock(&g_print.mutex);
		g_print.val = 1;
	}
	else
	{
		while (g_print.val == 1)
			;
		get_print_mutex();
	}
}
