/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 00:44:25 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/22 00:13:20 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		must_eat_cnt(void)
{
	int		idx;
	int		must_eat;

	if (g_param.number_of_times_each_philosopher_must_eat > 0)
	{
		idx = 0;
		must_eat = 0;
		while (idx < g_param.number_of_philosophers)
		{
			if (g_thd[idx].eat
				>= g_param.number_of_times_each_philosopher_must_eat)
				must_eat++;
			idx++;
		}
		if (must_eat == g_param.number_of_philosophers)
			return (1);
	}
	return (0);
}

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
