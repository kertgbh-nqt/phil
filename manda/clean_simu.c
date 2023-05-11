/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_simu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-garr <mel-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:01:17 by mel-garr          #+#    #+#             */
/*   Updated: 2023/05/09 14:01:17 by mel-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_simu(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->food);
	pthread_mutex_destroy(&data->is_writing);
	pthread_mutex_destroy(&data->left_to_eat_m);
	pthread_mutex_destroy(&data->simu_status_m);
	pthread_mutex_destroy(&data->all_eat_m);
	free(data->philos);
	free(data->forks);
	free(data);
	return (0);
}
