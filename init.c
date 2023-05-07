#include "philo.h"

int ft_init_philo(t_data *data)
{
    int i;

    i = 0;
    while (i < data->philo_nbr)
    {
        data->philos[i].index = i + 1;
        data->philos[i].left_to_eat = 0;
        data->philos[i].my_right_fork_id = i;
        data->philos[i].my_mate_fork_id = (i + 1) % data->philo_nbr;
        data->philos[i].data = data;
        i++;
    }
    return (0);
}

int ft_init_global_mutex(t_data *data)
{
    int i;

    i = 0;
    while (i < data->philo_nbr)
    {
        if (pthread_mutex_init(&(data->forks[i]), NULL))
            return (-1);
        i++;
    }
    if (pthread_mutex_init(&(data->is_writing), NULL))
        return (-1);
    if (pthread_mutex_init(&(data->food),NULL))
        return (-1);
    return (0);
}

int ft_init_more_data(t_data *data)
{
    data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
    if (!data->philos)
        return (-1);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nbr);
    if (!data->forks)
        return (free(data->philos) ,-1);
    if (ft_init_global_mutex(data) == -1)
        return (free(data->philos), free(data->forks), -1);
    if (ft_init_philo(data) == -1)
         return (free(data->philos), free(data->forks), -1);
    return (0);
}