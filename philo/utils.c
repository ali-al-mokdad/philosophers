/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:07:30 by marvin            #+#    #+#             */
/*   Updated: 2025/05/13 23:07:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_timestamp_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void precise_usleep(long time_ms)
{
    long start = get_timestamp_ms();
    while ((get_timestamp_ms() - start) < time_ms)
        usleep(500);
}

void print_status(t_philo *philo, const char *status)
{
    pthread_mutex_lock(&philo->data->log_mutex);
    if (!philo->data->simulation_end)
        printf("%ld %d %s\n",
            get_timestamp_ms() - philo->data->start_time,
            philo->id, status);
    pthread_mutex_unlock(&philo->data->log_mutex);
}
