#include "philo.h"

int clean_simu(t_data *data)
{
    int i;

    i = -1;
     while (++i < data->philo_nbr)
        pthread_detach(data->philos[i].thread);
    i = -1;
    while(++i < data->philo_nbr)
        pthread_mutex_destroy(&data->forks[i]);
    pthread_mutex_destroy(&data->food);
    pthread_mutex_destroy(&data->is_writing);
       free (data->philos);
        free(data->forks);
    return (0);
}