/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_simu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: mel-garr <mel-garr@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/05/07 08:14:38 by mel-garr          #+#    #+#             */
/*   Updated: 2023/05/07 08:14:38 by mel-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	clean_simu(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->philo_nbr)
		pthread_detach(data->philos[i].thread);
	i = -1;
	while (++i < data->philo_nbr)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->food);
	pthread_mutex_destroy(&data->is_writing);
	free(data->philos);
	free(data->forks);
	return (0);
}