/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superviser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-garr <mel-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:55:49 by mel-garr          #+#    #+#             */
/*   Updated: 2023/05/07 09:55:49 by mel-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	check_death(t_data *data, t_philo *philo)
{
	int	i;
	int	t;

	i = -1;
	while (++i < data->philo_nbr && data->simu_status == ON)
	{
		pthread_mutex_lock(&data->food);
		t = (int)get_time_ms() - philo[i].last_meal_time;
		if (t >= data->time_to_die
			|| (t >= data->time_to_die && data->philo_nbr == 1))
		{
			print_routine("died", &philo[i], NEED_TO_STOP);
			data->simu_status = OFF;
		}
		pthread_mutex_unlock(&data->food);
	}
}

void	check_all_eat(t_data *data)
{
	pthread_mutex_lock(&data->all_eat_m);
		data->all_eat = 0;
	pthread_mutex_unlock(&data->all_eat_m);
}

int	calculat_who_eat(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (data->need_to_eat != 0
		&& i < data->philo_nbr && data->philo_nbr != 1)
	{
		pthread_mutex_lock(&data->left_to_eat_m);
		if (philo[i].left_to_eat >= data->need_to_eat)
			i++;
		pthread_mutex_unlock(&data->left_to_eat_m);
	}
	return (i);
}

void	superviser(t_data *data, t_philo *philo)
{
	int	i;

	while (data->all_eat != data->philo_nbr)
	{
		check_death(data, philo);
		if (data->simu_status == OFF)
			break ;
		if (data->need_to_eat != -1)
		{
			i = calculat_who_eat(data, philo);
			if (i == data->philo_nbr && data->philo_nbr != 1)
			{				
				pthread_mutex_lock(&data->simu_status_m);
				data->simu_status = OFF;
				pthread_mutex_unlock(&data->simu_status_m);
				break ;
			}
		}
		check_all_eat(data);
	}
}
