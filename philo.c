/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeson <hyeson@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:24:36 by hyeson            #+#    #+#             */
/*   Updated: 2025/08/13 16:28:03 by hyeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_units	*get_units(int argc, char **argv)
{
	t_units	*units;

	units = (t_units *)malloc(sizeof(t_units));
	units->size = ft_atoi(argv[1]);
	units->wait = 1;
	units->activate = 1;
	units->init_time = 0;
	units->time_to_die = ft_atoi(argv[2]) * 1000;
	units->time_to_eat = ft_atoi(argv[3]) * 1000;
	units->time_to_sleep = ft_atoi(argv[4]) * 1000;
	pthread_mutex_init(&units->print_lock, NULL);
	if (argc == 6)
		units->must_eat = ft_atoi(argv[5]);
	else
		units->must_eat = -1;
	return (units);
}

t_philo	**init_philos(t_philo **philos, t_units *units)
{
	size_t	i;

	i = 0;
	while (i < units->size)
	{
		philos[i] = malloc(sizeof(t_philo));
		philos[i]->l_fork = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philos[i]->l_fork, NULL);
		philos[i]->cnt = 0;
		philos[i]->checked = 0;
		philos[i]->start_time = 0;
		philos[i]->dur = 0;
		philos[i]->num = i + 1;
		philos[i]->units = units;
		i++;
	}
	i = 0;
	while (i < units->size)
	{
		philos[i]->r_fork = philos[(i + 1) % units->size]->l_fork;
		i++;
	}
	return (philos);
}

void	*time_check(void *arg)
{
	t_philo	**philos;
	size_t	i;

	philos = (t_philo **)arg;
	while (philos[0]->units->wait)
		usleep(100);
	i = 0;
	while (philos[0]->units->activate)
	{
		if (philos[i]->start_time != 0)
			philos[i]->dur = get_now() - philos[i]->start_time;
		i++;
		if (i == philos[0]->units->size)
			i = 0;
		usleep(3000);
	}
	return (NULL);
}

void	philos_monitor(t_philo **philos, t_units *units)
{
	size_t	i;
	size_t	enough;

	i = 0;
	enough = 0;
	units->init_time = get_now();
	units->wait = 0;
	while (philos[i]->dur < units->time_to_die)
	{
		if (philos[i]->cnt >= units->must_eat && !philos[i]->checked)
		{
			philos[i]->checked = 1;
			enough++;
		}
		if (enough == units->size)
			break ;
		i++;
		if (i == units->size)
			i = 0;
	}
	units->activate = 0;
	if (philos[i]->dur >= units->time_to_die)
		dying_msg(philos[i]);
}

int	main(int argc, char *argv[])
{
	size_t		i;
	t_units		*units;
	t_philo		**philos;
	pthread_t	time_keeper;

	if (!(argc == 5 || argc == 6) || ft_atoi(argv[1]) < 1)
		return (0);
	units = get_units(argc, argv);
	philos = (t_philo **)malloc(sizeof(t_philo *) * (units->size));
	philos = init_philos(philos, units);
	i = 0;
	while (i < units->size)
	{
		pthread_create(&philos[i]->thr, NULL, thr_start, philos[i]);
		i++;
	}
	usleep(1000);
	pthread_create(&time_keeper, NULL, time_check, philos);
	philos_monitor(philos, units);
	i = 0;
	while (i < units->size)
		pthread_join(philos[i++]->thr, NULL);
	pthread_join(time_keeper, NULL);
	memory_clean(philos, units);
}
