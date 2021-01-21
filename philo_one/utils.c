/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 22:21:00 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/21 00:45:10 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_usleep(int wait)
{
	int				goal;

	goal = cal_timeval(g_param.bgn) + wait;
	while (goal > cal_timeval(g_param.bgn))
		;
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, &(*s), 1);
		s++;
	}
}

void	init(int n, long long *num, int *sign, int *len)
{
	*num = n;
	*len = 0;
	*sign = 1;
	if (*num < 0)
	{
		*len = *len + 1;
		*sign = -1;
		*num = *sign * *num;
	}
	while (*num != 0)
	{
		*num = *num / 10;
		*len = *len + 1;
	}
	if (n == 0)
		*len = 1;
}

char	*ft_itoa(int n)
{
	char		*rtn;
	long long	num;
	int			i;
	int			sign;
	int			len;

	init(n, &num, &sign, &len);
	rtn = (char *)malloc(sizeof(char) * (len + 1));
	if (!rtn)
		return (0);
	if (n == 0)
		rtn[0] = '0';
	if (sign == -1)
		rtn[0] = '-';
	num = n;
	num = sign * num;
	i = len - 1;
	while (num != 0)
	{
		rtn[i] = num % 10 + '0';
		num = num / 10;
		i--;
	}
	rtn[len] = '\0';
	return (rtn);
}

int		ft_atoi(const char *nptr)
{
	int sign;
	int dec;

	while (*nptr == '\n' || *nptr == '\t' || *nptr == ' '
		|| *nptr == '\v' || *nptr == '\r' || *nptr == '\f')
		nptr++;
	sign = 1;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	dec = 0;
	while (*nptr)
	{
		if (*nptr < '0' || *nptr > '9')
			return (-1);
		dec = *nptr - '0' + dec * 10;
		nptr++;
	}
	return (dec * sign);
}
