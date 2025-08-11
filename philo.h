/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeson <hyeson@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:15:52 by hyeson            #+#    #+#             */
/*   Updated: 2025/08/11 14:26:29 by hyeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_units
{
	size_t			wait;
	size_t			size;
	size_t			activate;
	size_t			must_eat;
	suseconds_t		time_to_die;
	suseconds_t		time_to_eat;
	suseconds_t		time_to_sleep;
}	t_units;

typedef struct s_philo
{
	size_t			num;
	size_t			cnt;
	size_t			checked;
	suseconds_t		dur;
	suseconds_t		start;
	pthread_t		thr;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_units			*units;
}	t_philo;

suseconds_t	get_now(void);
void		*thr_start(void *arg);

#endif /* PHILO_H */