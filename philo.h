/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeson <hyeson@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:15:52 by hyeson            #+#    #+#             */
/*   Updated: 2025/08/14 17:29:58 by hyeson           ###   ########.fr       */
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
	size_t			size;
	size_t			activate;
	size_t			must_eat;
	suseconds_t		init_time;
	suseconds_t		time_to_die;
	suseconds_t		time_to_eat;
	suseconds_t		time_to_sleep;
	pthread_mutex_t *activate_lock;
	pthread_mutex_t	*print_lock;
}	t_units;

typedef struct s_philo
{
	size_t			num;
	size_t			cnt;
	size_t			eating;
	size_t			checked;
	suseconds_t		dur;
	suseconds_t		start_time;
	pthread_t		thr;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_units			*units;
}	t_philo;

suseconds_t	get_now(void);
void		*thr_start(void *arg);
void		state_print(t_philo *philo, char *state);
void		dying_msg(t_philo *philo);
void		memory_clean(t_philo **philos, t_units *units);
void		not_activate(t_units *units);
int			ft_atoi(const char *s);
int			is_activate(t_units *units);

#endif /* PHILO_H */