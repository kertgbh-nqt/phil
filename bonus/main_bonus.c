/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: mel-garr <mel-garr@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/05/07 08:16:38 by mel-garr          #+#    #+#             */
/*   Updated: 2023/05/07 08:16:38 by mel-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data data;

	if (ac == 5 || ac == 6)
	{
		if (fill_struct(av, &data) == -1)
			return (ft_print_fd(2, "bad input\n"), 3);
		if (ft_init_more_data(&data) == -1)
			return (ft_print_fd(2, "pb initialing data\n"), 4);
		if (start_simulation(&data) == -1)
			return (ft_print_fd(2, "couldnt do ths simulation\n"), 5);
		if (clean_simu(&data) == -1)
			return (ft_print_fd(2, "couldn't free correctly\n"), 6);
	}
	else
		return (ft_print_fd(2, "bad nbr of arguments\n"), 2);
	system("leaks a.out");
	return (0);
}
