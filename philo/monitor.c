/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:08:42 by marvin            #+#    #+#             */
/*   Updated: 2025/05/13 23:08:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool all_philos_ate_enough(t_data *data)
{
    int i;

    if (data->meals_required <= 0)
        return false;

    for (i = 0; i < data->number_of_philos; i++)
    {
        if (data->philos[i].meals_eaten < data->meals_required)
            return false;
    }
    return true;
}

void *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (!data->simulation_end)
    {
        for (i = 0; i < data->number_of_philos; i++)
        {
            pthread_mutex_lock(&data->meal_mutex);
            long time_since_last_meal = get_timestamp_ms() - data->philos[i].last_meal;
            if (time_since_last_meal > data->time_to_die)
            {
                pthread_mutex_lock(&data->log_mutex);
                if (!data->simulation_end)
                {
                    data->simulation_end = true;
                    printf("%ld %d died\n",
                        get_timestamp_ms() - data->start_time,
                        data->philos[i].id);
                }
                pthread_mutex_unlock(&data->log_mutex);
                pthread_mutex_unlock(&data->meal_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&data->meal_mutex);
        }
        if (all_philos_ate_enough(data))
        {
            pthread_mutex_lock(&data->log_mutex);
            data->simulation_end = true;
            pthread_mutex_unlock(&data->log_mutex);
            return NULL;
        }
        usleep(1000); // Check every 1ms
    }
    return NULL;
}
