/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 19:06:41 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/27 23:58:31 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ps_wait(void)
{
	int		idx;
	int		status;

	idx = 0;
	while (idx < g_param.number_of_philosophers)
	{
		if (idx == g_param.number_of_philosophers - 1)
			kill(g_ps.pid[idx], SIGINT);
		waitpid(g_ps.pid[idx], &status, 0);
		idx++;
		if (WEXITSTATUS(status) == 1)
		{
			while (idx < g_param.number_of_philosophers)
				kill(g_ps.pid[idx++], SIGINT);
		}
	}
}

int		ps_create(void)
{
	int		idx;

	idx = 0;
	while (idx < g_param.number_of_philosophers)
	{
		g_ps.pid[idx] = fork();
		if (g_ps.pid[idx] == 0)
			child_ps(g_ps.name[idx]);
		else if (g_ps.pid < 0)
			return (-1);
		idx++;
	}
	ps_wait();
	return (0);
}

sem_t	*init_semaphore(char *name, int value)
{
	sem_t *sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT, 0644, value);
	if (sem == SEM_FAILED)
		return (NULL);
	return (sem);
}

void	init_malloc(void)
{
	int		idx;

	g_ps.pid = (pid_t *)malloc(sizeof(pid_t) * g_param.number_of_philosophers);
	g_ps.name = (char **)malloc(
				sizeof(char *) * g_param.number_of_philosophers);
	g_ps.eat = 0;
	g_ps.last_eat = 0;
	idx = 0;
	while (idx < g_param.number_of_philosophers)
	{
		g_ps.name[idx] = ft_itoa(idx + 1);
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
