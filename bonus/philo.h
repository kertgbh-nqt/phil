/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: mel-garr <mel-garr@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/05/07 08:17:16 by mel-garr          #+#    #+#             */
/*   Updated: 2023/05/07 08:17:16 by mel-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ON 0
# define OFF 1

# define CAN_WRITE 1
# define NEED_TO_STOP 0

# define FORK 3
# define EAT 4
# define SLEEP 5
# define THINK 6
# define DEAD 7

typedef struct s_data t_data;

typedef struct s_philo
{
	pthread_t thread;
	t_data *data;
	int left_to_eat;
	int index;
	int my_right_fork_id;
	int my_mate_fork_id;

	unsigned long last_meal_time;

} t_philo;

typedef struct s_data
{
	int philo_nbr;
	int all_eat; //how many one full ate
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int need_to_eat;
	t_philo *philos;
	int simu_status;
	unsigned long sst; //starting time

	pthread_mutex_t *forks;
	pthread_mutex_t is_writing;
	pthread_mutex_t food;
} t_data;

void	ft_print_fd(int fd, char *str);
int	fill_struct(char **str, t_data *data);
unsigned long	get_time_ms(void);
int	start_simulation(t_data *data);
int	ft_init_more_data(t_data *data);
void	print_routine(char *str, t_philo *philo, int superviser);
void	new_usleep(unsigned long duration, t_data *data);
void	superviser(t_data *data, t_philo *philo);
int	clean_simu(t_data *data);

//need to recheck new_usleep

#endif
