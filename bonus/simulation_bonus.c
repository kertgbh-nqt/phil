/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-garr <mel-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:56:10 by mel-garr          #+#    #+#             */
/*   Updated: 2023/05/07 09:56:10 by mel-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->my_right_fork_id]);
	print_routine("has taken a fork", philo, CAN_WRITE);
	pthread_mutex_lock(&philo->data->forks[philo->my_mate_fork_id]);
	print_routine("has taken a fork", philo, CAN_WRITE);
	pthread_mutex_lock(&philo->data->food);
	print_routine("is eating", philo, CAN_WRITE);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->data->food);
	new_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->left_to_eat_m);
	philo->left_to_eat++;
	pthread_mutex_unlock(&philo->data->left_to_eat_m);
	pthread_mutex_unlock(&philo->data->forks[philo->my_right_fork_id]);
	pthread_mutex_unlock(&philo->data->forks[philo->my_mate_fork_id]);
}

void	*simulation(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->index % 2 && philo->data->philo_nbr > 1)
		usleep(10000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->simu_status_m);
		if (philo->data->simu_status)
			break ;
		pthread_mutex_unlock(&philo->data->simu_status_m);
		pthread_mutex_lock(&philo->data->all_eat_m);
		if (philo->data->all_eat != 0)
			break ;
		pthread_mutex_unlock(&philo->data->all_eat_m);
		philo_eat(philo);
		print_routine("is sleeping", philo, CAN_WRITE);
		new_usleep(philo->data->time_to_sleep);
		print_routine("is thinking", philo, CAN_WRITE);
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int	i;

	i = -1;
	data->sst = get_time_ms();
	while (++i < data->philo_nbr)
	{
		data->philos[i].last_meal_time = get_time_ms();
		if (pthread_create(&(data->philos[i].thread), NULL, simulation,
				&(data->philos[i])))
			return (-1);
	}
	superviser(data, data->philos);
	pthread_mutex_unlock(&data->is_writing);
	return (1);
}
