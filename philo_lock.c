/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeson <hyeson@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:28:12 by hyeson            #+#    #+#             */
/*   Updated: 2025/08/15 14:11:59 by hyeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	state_print(t_philo *philo, char *state)
{
	if (is_activate(philo->units))
	{
		pthread_mutex_lock(philo->units->print_lock);
		printf("%ld %ld %s\n", (get_now() - philo->units->init_time)
			/ 1000, philo->num, state);
		pthread_mutex_unlock(philo->units->print_lock);
	}
}

void	dying_msg(t_philo *philo)
{
	pthread_mutex_lock(philo->units->print_lock);
	printf("%ld %ld is died\n",
		(get_now() - philo->units->init_time) / 1000, philo->num);
	pthread_mutex_unlock(philo->units->print_lock);
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
