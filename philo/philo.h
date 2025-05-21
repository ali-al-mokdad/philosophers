/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:20:30 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/05/14 15:37:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include "stdio.h"
#include "string.h"
#include "sys/time.h"
#include "stdlib.h"
#include "signal.h"
#include "sys/wait.h"
#include "semaphore.h"
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_data t_data;

typedef struct s_philo {
    int             id;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long            last_meal;
    int             meals_eaten;
    t_data          *data;
} t_philo;

typedef struct s_data {
    int             number_of_philos;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    int             meals_required;
    bool            simulation_end;

    long            start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t log_mutex;
    pthread_mutex_t meal_mutex;

    t_philo         *philos;
} t_data;

long    get_timestamp_ms(void);
void    precise_usleep(long time_ms);
void    print_status(t_philo *philo, const char *status);
int     init_all(t_data *data, int argc, char **argv);
void    *philosopher_routine(void *arg);
void    *monitor_routine(void *arg);

#endif


