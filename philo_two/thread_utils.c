/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 00:44:25 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/21 00:46:46 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
	ft_putstr_fd(tmp, 1);
	free(tmp);
	ft_putstr_fd("ms ", 1);
	ft_putstr_fd(philo_name, 1);
	ft_putstr_fd(sentence, 1);
}
