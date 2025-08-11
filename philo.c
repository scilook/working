/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeson <hyeson@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:24:36 by hyeson            #+#    #+#             */
/*   Updated: 2025/08/11 17:33:40 by hyeson           ###   ########.fr       */
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
	units->time_to_die = ft_atoi(argv[2]) * 1000;
	units->time_to_eat = ft_atoi(argv[3]) * 1000;
	units->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		units->must_eat = ft_atoi(argv[5]);
	else
		units->must_eat = 0xFFFFFFFFFFFF;
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
		philos[i]->r_fork = malloc(sizeof(pthread_mutex_t));
		philos[i]->units = malloc(sizeof(t_units));
		pthread_mutex_init(philos[i]->l_fork, NULL);
		philos[i]->cnt = 0;
		philos[i]->checked = 0;
		philos[i]->start = get_now();
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
	i = 0;
	while (philos[i]->dur < philos[i]->units->time_to_die)
	{
		philos[i]->dur = get_now() - philos[i]->start;
		i++;
		if (i == philos[i]->units->size)
			i = 0;
	}
	return (philos);
}

void	philos_monitor(t_philo **philos, t_units *units)
{
	size_t	i;
	size_t	enough;

	i = 0;
	enough = 0;
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
	usleep(1000);
	if (philos[i]->dur > units->time_to_die)
		printf("%ld %ld is died\n", get_now() / 1000, philos[i]->num);
	printf("%ld %ld is died\n", philos[i]->dur, philos[i]->start);
}

int	main(int argc, char *argv[])
{
	size_t		i;
	t_units		*units;
	t_philo		**philos;
	pthread_t	time_keeper;

	if (!(argc == 5 || argc == 6))
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
	pthread_create(&time_keeper, NULL, time_check, philos);
	pthread_detach(time_keeper);
	philos_monitor(philos, units);
	i = 0;
	while (i < units->size)
		pthread_join(philos[i++]->thr, NULL);
}
