/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:07:11 by marvin            #+#    #+#             */
/*   Updated: 2025/05/13 23:07:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void take_forks(t_philo *philo)
{
    // if (philo->id % 2 == 0)
    // {
    //     pthread_mutex_lock(&philo->forks[philo->left_fork]);  // Always pick up left fork first
    //     pthread_mutex_lock(&philo->forks[philo->right_fork]); // Then pick up right fork
    // }
    // else
    // {
    //     pthread_mutex_lock(&philo->forks[philo->right_fork]); // Pick up right fork first
    //     pthread_mutex_lock(&philo->forks[philo->left_fork]);  // Then pick up left fork
    // }

    pthread_mutex_lock(philo->left_fork);
    print_status(philo, "has taken a fork");

    if (philo->left_fork == philo->right_fork)
    {
        // Only one fork exists; wait and simulate death
        while (!philo->data->simulation_end)
            usleep(100); // Let monitor detect starvation
        return;
    }

    pthread_mutex_lock(philo->right_fork);
    print_status(philo, "has taken a fork");
}


static void drop_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    if (philo->left_fork != philo->right_fork)
        pthread_mutex_unlock(philo->right_fork);
}

static void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->meal_mutex);
    philo->last_meal = get_timestamp_ms();
    print_status(philo, "is eating");
    pthread_mutex_unlock(&philo->data->meal_mutex);

    precise_usleep(philo->data->time_to_eat);
    philo->meals_eaten++;
}

static void sleep_and_think(t_philo *philo)
{
    print_status(philo, "is sleeping");
    precise_usleep(philo->data->time_to_sleep);
    print_status(philo, "is thinking");
}

void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    // Delay even philosophers to avoid simultaneous fork grabs
    if (philo->id % 2 == 0)
        usleep(1000);

    while (!philo->data->simulation_end)
    {
        take_forks(philo);
        eat(philo);
        drop_forks(philo);
        if (philo->data->meals_required > 0 &&
            philo->meals_eaten >= philo->data->meals_required)
            break;
        sleep_and_think(philo);
    }
    return NULL;
}
