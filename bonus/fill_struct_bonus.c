/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-garr <mel-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:47:58 by mel-garr          #+#    #+#             */
/*   Updated: 2023/05/09 11:47:58 by mel-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	fill_phase_one(int unsigned num, int i, t_data *data)
{
	if (i == 1)
	{
		if (num == 0)
			return (-1);
		data->philo_nbr = num;
	}
	else if (i == 2)
		data->time_to_die = num;
	else if (i == 3)
		data->time_to_eat = num;
	else if (i == 4)
		data->time_to_sleep = num;
	else if (i == 5)
	{
		data->need_to_eat = num;
		if (num == 0)
			return (-1);
	}
	return (0);
}

int	get_num(char *str)
{
	int			i;
	long		result;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		result = (result * 10) + str[i] - 48;
		i++;
		if (result > 2147483647)
			return (-1);
	}
	return ((int)result);
}

int	fill_struct(char **str, t_data *data)
{
	int		i;
	int		num;

	i = 1;
	while (str[i])
	{
		num = get_num(str[i]);
		if (num == -1)
			return (-1);
		if (fill_phase_one(num, i, data) == -1)
			return (-1);
		i++;
	}
	if (i == 5)
		data->need_to_eat = -1;
	data->simu_status = ON;
	data->all_eat = 0;
	return (0);
}
