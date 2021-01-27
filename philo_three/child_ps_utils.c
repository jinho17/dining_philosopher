/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_ps_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:16:04 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/27 23:59:57 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		cal_timeval(struct timeval bgn)
{
	struct timeval	end;
	int				diff;

	gettimeofday(&end, NULL);
	diff = (end.tv_sec - bgn.tv_sec) * 1000
			+ (end.tv_usec - bgn.tv_usec) * 0.001;
	return (diff);
}

void	print_sentence(char *philo_name, char *sentence)
{
	char			*tmp;

	tmp = ft_itoa(cal_timeval(g_param.bgn));
	sem_wait(g_sem.print);
	ft_putstr_fd(tmp, 1);
	ft_putstr_fd("ms ", 1);
	ft_putstr_fd(philo_name, 1);
	ft_putstr_fd(sentence, 1);
	sem_post(g_sem.print);
	free(tmp);
}
