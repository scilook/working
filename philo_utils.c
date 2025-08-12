/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeson <hyeson@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:23:36 by hyeson            #+#    #+#             */
/*   Updated: 2025/08/12 16:12:17 by hyeson           ###   ########.fr       */
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

void	state_print(t_philo *philo, char *state)
{
	if (philo->units->activate)
	{
		pthread_mutex_lock(&philo->units->print_lock);
		if (philo->units->activate)
			printf("%ld %ld %s\n",
				(get_now() - philo->units->init_time) / 1000, philo->num, state);
		pthread_mutex_unlock(&philo->units->print_lock);
	}
}

void	dying_msg(t_philo *philo)
{
	pthread_mutex_lock(&philo->units->print_lock);
	printf("%ld %ld is died\n",
		(get_now() - philo->units->init_time) / 1000, philo->num);
	pthread_mutex_unlock(&philo->units->print_lock);
}

void	memory_clean(t_philo **philos, t_units *units)
{
	size_t	i;

	pthread_mutex_destroy(&units->print_lock);
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
