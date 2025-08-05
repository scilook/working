/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeson <hyeson@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:24:36 by hyeson            #+#    #+#             */
/*   Updated: 2025/08/05 21:49:38 by hyeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_units	*get_units(int argc, char **argv)
{
	t_units	*units;

	units = (t_units *)malloc(sizeof(t_units));
	units->size = ft_atoi(argv[1]);
	units->time_to_die = ft_atoi(argv[2]) * 1000;
	units->time_to_eat = ft_atoi(argv[3]) * 1000;
	units->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		units->must_eat = ft_atoi(argv[5]);
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

void	philos_monitor(t_philo **philos)
{

}

int	main(int argc, char *argv[])
{
	ssize_t		i;
	t_units		*units;
	t_philo		**philos;

	if (!(argc == 5 || argc == 6))
		return (0);
	units = get_units(argc, argv);
	philos = (t_philo **)malloc(sizeof(t_philo *) * (units->size));
	philos = init_philos(philos, units);
	i = -1;
	while (++i < units->size)
		pthread_create(&philos[i]->thr, NULL, thr_start, philos[i]);
	monitor(philos);
	i = -1;
	while (++i < units->size)
		pthread_join(philos[i]->thr, NULL);
}
