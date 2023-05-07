/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superviser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: mel-garr <mel-garr@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/05/07 08:18:51 by mel-garr          #+#    #+#             */
/*   Updated: 2023/05/07 08:18:51 by mel-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	superviser(t_data *data, t_philo *philo)
{
	int i;
	int t;
	while (data->all_eat != data->philo_nbr)
	{
		i = -1;
		while (++i < data->philo_nbr && data->simu_status == ON)
		{
			pthread_mutex_lock(&data->food);
			t = (int)get_time_ms() - philo[i].last_meal_time;
			if (t >= data->time_to_die)
			{
				print_routine("died", &philo[i], NEED_TO_STOP);
				data->simu_status = OFF;
			}
			pthread_mutex_unlock(&data->food);
		}
		if (data->simu_status == OFF)
			break ;
		if (data->need_to_eat != -1)
		{
			i = 0;
			while (data->need_to_eat != 0 && i < data->philo_nbr
				&& philo[i].left_to_eat >= data->need_to_eat)
				i++;
			if (i == data->philo_nbr)
			{
				data->simu_status = OFF;
				break ;
			}
		}
		data->all_eat = 0;
	}
}
