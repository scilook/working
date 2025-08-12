/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeson <hyeson@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:41:33 by hyeson            #+#    #+#             */
/*   Updated: 2025/08/12 16:48:21 by hyeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Entry section
static void	thinking_time(t_philo *philo)
{
	state_print(philo, "is thinking");
	usleep(500);
	// if (philo->l_fork == philo->r_fork)
	// {
	// 	pthread_mutex_lock(philo->r_fork);
	// 	state_print(philo, "has taken a fork");
	// }
	if (philo->num % 2)
	{
		pthread_mutex_lock(philo->r_fork);
		state_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		state_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		state_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		state_print(philo, "has taken a fork");
	}
}

//Critical section
static void	eating_time(t_philo *philo)
{
	if (philo->units->activate)
	{
		philo->start_time = get_now();
		state_print(philo, "is eating");
		usleep(philo->units->time_to_eat);
		philo->cnt++;
	}
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->start_time = get_now();
}

//Exit section
static void	sleeping_time(t_philo *philo)
{
	if (philo->units->activate)
	{
		state_print(philo, "is sleeping");
		usleep(philo->units->time_to_sleep);
	}
}

void	*thr_start(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (philo->units->wait)
		usleep(100);
	philo->start_time = get_now();
	if (philo->num % 2)
		usleep(300);
	while (philo->units->activate)
	{
		thinking_time(philo);
		eating_time(philo);
		sleeping_time(philo);
	}
	return (NULL);
}
