/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeson <hyeson@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:23:36 by hyeson            #+#    #+#             */
/*   Updated: 2025/08/15 14:12:02 by hyeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	get_now(void)
{
	struct timeval	tv;
	suseconds_t		ts;

	gettimeofday(&tv, NULL);
	ts = tv.tv_sec * 1000 * 1000 + tv.tv_usec;
	return (ts);
}

int	ft_atoi(const char *s)
{
	size_t	i;
	int		result;
	int		flag;

	i = 0;
	result = 0;
	flag = 1;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-')
	{
		flag = -1;
		i++;
	}
	else if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + ((char)s[i] - '0');
		i++;
	}
	return (flag * result);
}
