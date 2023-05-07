/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-garr <mel-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:56:19 by mel-garr          #+#    #+#             */
/*   Updated: 2023/05/07 09:56:19 by mel-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_fd(int fd, char *str)
{
	int i;

	i = -1;
	while (str[++i])
		write(fd, &str[i], 1);
}

void	print_routine(char *str, t_philo *philo, int superviser)
{
	unsigned int time_to_write;

	time_to_write = get_time_ms() - philo->data->sst;
	pthread_mutex_lock(&philo->data->is_writing);
	if (philo->data->simu_status == ON && philo->data->need_to_eat != 0)
		printf("%u %d %s\n", time_to_write, philo->index, str);
	if (superviser == CAN_WRITE)
		pthread_mutex_unlock(&philo->data->is_writing);
}
