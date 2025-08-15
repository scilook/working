/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeson <hyeson@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:41:33 by hyeson            #+#    #+#             */
/*   Updated: 2025/08/15 14:38:57 by hyeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Entry section
static void	single_philo_never_eat_spaghetti(t_philo *philo)
{
	state_print(philo, "is thinking");
	pthread_mutex_lock(philo->r_fork);
	state_print(philo, "has taken a fork");
	pthread_mutex_unlock(philo->r_fork);
}

static void	thinking_time(t_philo *philo)
{
	state_print(philo, "is thinking");
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
	if (is_activate(philo->units))
	{
		philo->eating = 1;
		state_print(philo, "is eating");
		usleep(philo->units->time_to_eat);
		philo->cnt++;
	}
	philo->start_time = get_now();
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->eating = 0;
}

//Exit section
static void	sleeping_time(t_philo *philo)
{
	if (is_activate(philo->units))
	{
		state_print(philo, "is sleeping");
		usleep(philo->units->time_to_sleep);
	}
}

void	*thr_start(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->units->activate_lock);
	pthread_mutex_unlock(philo->units->activate_lock);
	philo->start_time = get_now();
	if (philo->num % 2)
		usleep(500);
	if (philo->l_fork == philo->r_fork)
	{
		single_philo_never_eat_spaghetti(philo);
		return (NULL);
	}
	while (is_activate(philo->units))
	{
		thinking_time(philo);
		eating_time(philo);
		sleeping_time(philo);
		usleep(500);
	}
	return (NULL);
}
