/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:41:58 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/26 17:57:19 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	get_sem_print(char *philo_name, char *str)
{
	if (g_print == 0)
	{
		g_print = 1;
		sem_wait(g_sem.print);
		print_sentence(philo_name, str);
		g_print = 0;
		sem_post(g_sem.print);
	}
	else
	{
		while (g_print != 0)
			;
		get_sem_print(philo_name, str);
	}
}

void	get_sem_fork(int fork, char *philo_name)
{
	if (g_fork[fork] == 0)
	{
		g_fork[fork] = 1;
		sem_wait(g_sem.fork);
		get_sem_print(philo_name, " has taken a fork\n");
	}
	else
	{
		while (g_fork[fork] != 0)
			;
		get_sem_fork(fork, philo_name);
	}
}
