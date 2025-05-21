/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:20:03 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/05/13 23:05:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_data data;
    if (init_all(&data, argc, argv) != 0)
        return (1);
    // Create monitor
    pthread_t monitor;
    pthread_create(&monitor, NULL, monitor_routine, &data);
    pthread_detach(monitor);
    // Create all philosopher threads
    for (int i = 0; i < data.number_of_philos; i++)
        pthread_create(&data.philos[i].thread, NULL, philosopher_routine, &data.philos[i]);
    for (int i = 0; i < data.number_of_philos; i++)
        pthread_join(data.philos[i].thread, NULL);
    return (0);
}

