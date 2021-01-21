/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 14:58:22 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/21 00:20:14 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	var_free(void)
{
	int		idx;

	idx = 0;
	while (idx < g_param.number_of_philosophers)
	{
		free(g_thd[idx].name);
		pthread_mutex_destroy(&g_fork[idx].mutex);
		idx++;
	}
	pthread_mutex_destroy(&g_print.mutex);
	free(g_thd);
	free(g_fork);
}

int		main(int argc, char *argv[])
{
	if (init_param(argc, argv) < 0)
	{
		ft_putstr_fd("Wrong argument!\n", 1);
		return (0);
	}
	init_malloc();
	if (thd_create() < 0)
	{
		ft_putstr_fd("Pthread create error!\n", 1);
		return (0);
	}
	thd_join();
	var_free();
}
