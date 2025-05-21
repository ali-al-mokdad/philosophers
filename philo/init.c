/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:05:48 by marvin            #+#    #+#             */
/*   Updated: 2025/05/13 23:05:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atol(const char *str)
{
	long	result = 0;
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	return result;
}

static int init_mutexes(t_data *data)
{
	int i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
	if (!data->forks)
		return 1;
	for (i = 0; i < data->number_of_philos; i++)
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return 1;

	if (pthread_mutex_init(&data->log_mutex, NULL) != 0)
		return 1;
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
		return 1;
	return 0;
}

static void init_philos(t_data *data)
{
	for (int i = 0; i < data->number_of_philos; i++)
	{
		t_philo *philo = &data->philos[i];
		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->last_meal = data->start_time;
		philo->left_fork = &data->forks[i];
		philo->right_fork = &data->forks[(i + 1) % data->number_of_philos];
		philo->data = data;
	}
}

int	init_all(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return 1;

	data->number_of_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->meals_required = (argc == 6) ? ft_atol(argv[5]) : -1;
	data->simulation_end = false;

	if (data->number_of_philos <= 0 || data->time_to_die < 0 ||
		data->time_to_eat < 0 || data->time_to_sleep < 0 ||
		(argc == 6 && data->meals_required <= 0))
		return 1;

	if (init_mutexes(data) != 0)
		return 1;

	data->philos = malloc(sizeof(t_philo) * data->number_of_philos);
	if (!data->philos)
		return 1;

	data->start_time = get_timestamp_ms();
	init_philos(data);
	return 0;
}
