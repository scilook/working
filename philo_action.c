/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeson <hyeson@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:41:33 by hyeson            #+#    #+#             */
/*   Updated: 2025/08/05 21:54:33 by hyeson           ###   ########.fr       */
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

void	thinking_time(t_philo *philo)
{
	printf("%ld %ld is thinking\n", get_now() / 1000, philo->num);
	if (philo->num % 2)
	{
		pthread_mutex_lock(philo->l_fork);
		printf("%ld %ld has taken a fork\n", get_now() / 1000, philo->num);
		pthread_mutex_lock(philo->r_fork);
		printf("%ld %ld has taken a fork\n", get_now() / 1000, philo->num);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		printf("%ld %ld has taken a fork\n", get_now() / 1000, philo->num);
		pthread_mutex_lock(philo->l_fork);
		printf("%ld %ld has taken a fork\n", get_now() / 1000, philo->num);
	}
}
//Critical section
void	eating_time(t_philo *philo)
{

}
//Exit section
void	sleeping_time(t_philo *philo)
{

}

void	*thr_start(void *arg)
{
	suseconds_t	ts;
	t_philo		*philo;

	philo = (t_philo *)arg;
	philo->start = get_now();
	while(philo->dur < philo->units->time_to_die)
	{
		thinking_time(philo);
		eating_time(philo);
		sleeping_time(philo);
		philo->cnt++;
	}
}
