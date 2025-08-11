/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeson <hyeson@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:41:33 by hyeson            #+#    #+#             */
/*   Updated: 2025/08/11 15:22:55 by hyeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Entry section
suseconds_t	get_now(void)
{
	struct timeval	tv;
	suseconds_t		ts;

	gettimeofday(&tv, NULL);
	ts = tv.tv_sec * 1000 * 1000 + tv.tv_usec;
	return (ts);
}

static void	thinking_time(t_philo *philo)
{
	if (philo->units->activate)
		printf("%ld %ld is thinking\n", get_now() / 1000, philo->num);
	if (philo->num % 2)
	{
		pthread_mutex_lock(philo->r_fork);
		if (philo->units->activate)
			printf("%ld %ld has taken a fork\n", get_now() / 1000, philo->num);
		pthread_mutex_lock(philo->l_fork);
		if (philo->units->activate)
			printf("%ld %ld has taken a fork\n", get_now() / 1000, philo->num);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		if (philo->units->activate)
			printf("%ld %ld has taken a fork\n", get_now() / 1000, philo->num);
		pthread_mutex_lock(philo->r_fork);
		if (philo->units->activate)
			printf("%ld %ld has taken a fork\n", get_now() / 1000, philo->num);
	}
}

//Critical section
static void	eating_time(t_philo *philo)
{
	philo->dur = 0;
	philo->start = 0;
	if (philo->units->activate)
	{
		printf("%ld %ld is eating\n", get_now() / 1000, philo->num);
		usleep(philo->units->time_to_eat);
		philo->cnt++;
	}
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->start = get_now();
}

//Exit section
static void	sleeping_time(t_philo *philo)
{
	if (philo->units->activate)
	{
		printf("%ld %ld is sleeping\n", get_now() / 1000, philo->num);
		usleep(philo->units->time_to_sleep);
	}
}

void	*thr_start(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	philo->start = get_now();
	while (philo->units->wait);
	philo->start = get_now();
	if (philo->num % 2)
		usleep(500);
	while (philo->units->activate)
	{
		thinking_time(philo);
		eating_time(philo);
		sleeping_time(philo);
	}
	return (philo);
}
