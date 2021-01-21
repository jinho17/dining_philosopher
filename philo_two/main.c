/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 00:17:58 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/21 14:16:30 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	var_free(void)
{
	int		idx;

	idx = 0;
	while (idx < g_param.number_of_philosophers)
	{
		free(g_thd[idx].name);
		idx++;
	}
	free(g_thd);
	sem_close(g_sem);
	sem_unlink(SEM_NAME);
}

int		main(int argc, char *argv[])
{
	if (init_param(argc, argv) < 0)
	{
		ft_putstr_fd("Wrong argument!\n", 1);
		return (0);
	}
	init_malloc();
	g_sem = init_semaphore();
	if(g_sem == NULL)
	{
		ft_putstr_fd("Semaphore init error!\n", 1);
		return (0);
	}
	if (thd_create() < 0)
	{
		ft_putstr_fd("Pthread create error!\n", 1);
		return (0);
	}
	thd_join();
	var_free();
}
