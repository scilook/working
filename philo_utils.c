/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeson <hyeson@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:23:04 by hyeson            #+#    #+#             */
/*   Updated: 2025/04/29 16:57:20 by hyeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *s)
{
	size_t	i;
	int		result;
	int		flag;

	i = 0;
	result = 0;
	flag = 1;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-')
	{
		flag = -1;
		i++;
	}
	else if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + ((char)s[i] - '0');
		i++;
	}
	return (flag * result);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if ((nmemb * size) / nmemb != size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	memset(ptr, 0,nmemb * size);
	return (ptr);
}
