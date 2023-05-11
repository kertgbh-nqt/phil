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
	while (++i < data->philo_nbr)
	{
		pthread_mutex_lock(&philo->data->simu_status_m);
		if (data->simu_status == OFF)
			break ;
		pthread_mutex_unlock(&philo->data->simu_status_m);
		pthread_mutex_lock(&data->food);
		t = (int)get_time_ms() - philo[i].last_meal_time;
		if (t >= data->time_to_die)
		{
			print_routine("died", &philo[i], NEED_TO_STOP);
			pthread_mutex_lock(&philo->data->simu_status_m);
			data->simu_status = OFF;
			pthread_mutex_unlock(&philo->data->simu_status_m);
		}
		pthread_mutex_unlock(&data->food);
	}
}

void	check_all_eat(t_data *data, int i)
{
	pthread_mutex_lock(&data->all_eat_m);
	if (i == data->philo_nbr)
		data->all_eat = 1;
	else
		data->all_eat = 0;
	pthread_mutex_unlock(&data->all_eat_m);
}

int	calculat_who_eat(t_data *data, t_philo *philo)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < data->philo_nbr && data->philo_nbr != 1)
	{
		pthread_mutex_lock(&data->left_to_eat_m);
		if (philo[i].left_to_eat >= data->need_to_eat)
				j++;
		pthread_mutex_unlock(&data->left_to_eat_m);
			i++;
	}
	return (j);
}

void	superviser(t_data *data, t_philo *philo)
{
	int	i;

	while (!data->all_eat)
	{
		check_death(data, philo);
		pthread_mutex_lock(&data->simu_status_m);
		if (data->simu_status == OFF)
		{
			pthread_mutex_unlock(&data->simu_status_m);
			break ;
		}
		pthread_mutex_unlock(&data->simu_status_m);
		if (data->need_to_eat != -1)
		{
			i = calculat_who_eat(data, philo);
			if (i == data->philo_nbr)
			{	
				pthread_mutex_lock(&data->simu_status_m);
				data->simu_status = OFF;
				pthread_mutex_unlock(&data->simu_status_m);
			}
		}
		check_all_eat(data, i);
	}
}
