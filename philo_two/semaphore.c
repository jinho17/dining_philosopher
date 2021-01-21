/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:41:58 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/21 15:02:02 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	get_sem(int fork, char *philo_name)
{
	if (g_fork_idx == fork)
	{
		sem_wait(g_sem);
		if (g_fork_idx < g_param.number_of_philosophers)
			g_fork_idx++;
		else
			g_fork_idx = 0;
		print_sentence(philo_name, " has taken a fork\n");
	}
	else
	{
		while (g_fork_idx != fork)
			;
		get_sem(fork);
	}
}
