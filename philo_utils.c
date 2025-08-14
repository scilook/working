/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeson <hyeson@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:23:36 by hyeson            #+#    #+#             */
/*   Updated: 2025/08/14 17:59:59 by hyeson           ###   ########.fr       */
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

int	is_activate(t_units *units)
{
	int	bool;

	pthread_mutex_lock(units->activate_lock);
	bool = units->activate;
	pthread_mutex_unlock(units->activate_lock);
	return (bool);
}

void	not_activate(t_units *units)
{
	pthread_mutex_lock(units->activate_lock);
	units->activate = !units->activate;
	pthread_mutex_unlock(units->activate_lock);
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

void	memory_clean(t_philo **philos, t_units *units)
{
	size_t	i;

	pthread_mutex_destroy(units->print_lock);
	pthread_mutex_destroy(units->activate_lock);
	free(units->print_lock);
	free(units->activate_lock);
	i = 0;
	while (i < units->size)
	{
		pthread_mutex_destroy(philos[i]->l_fork);
		free(philos[i]->l_fork);
		free(philos[i]);
		i++;
	}
	free(philos);
	free(units);
}
