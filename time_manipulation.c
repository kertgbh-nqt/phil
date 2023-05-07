#include "philo.h"

unsigned long get_time_ms(void)
{
    struct timeval time;
    
    gettimeofday(&time, NULL);
    return (time.tv_sec * (unsigned long)1000 + time.tv_usec / 1000);
}

void    new_usleep(unsigned long duration, t_data *data)
{
    unsigned long start;

    start = get_time_ms();
    while(data->simu_status == ON)
    {
        if (get_time_ms() - start >= duration)
            break;
        usleep(data->philo_nbr * 2);
    }
}