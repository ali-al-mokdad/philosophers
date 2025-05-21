/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:15:17 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/05/21 16:15:17 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philosophers.h"

void	ft_philosophers(t_tools *tools)
{
	int	i;

	i = 0;
	while (i < tools->philo_num)
	{
		pthread_create(&tools->philos[i].thread,
			NULL, life_cycle, &tools->philos[i]);
		i++;
	}
	ft_monitor(tools);
}

void	get_fork_order(t_philo *philo, int *first, int *second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

void	eat(t_philo *philo)
{
	t_tools	*tools;
	int		first;
	int		second;

	tools = philo->tools;
	get_fork_order(philo, &first, &second);
	pthread_mutex_lock(&tools->forks[first]);
	print_status(tools, philo->id, "has taken a fork");
	pthread_mutex_lock(&tools->forks[second]);
	print_status(tools, philo->id, "has taken a fork");
	print_status(tools, philo->id, "is eating");
	pthread_mutex_lock(&tools->meal);
	philo->last_meal = current_time();
	philo->meal_num++;
	pthread_mutex_unlock(&tools->meal);
	usleep(tools->eat_time * 1000);
	pthread_mutex_unlock(&tools->forks[second]);
	pthread_mutex_unlock(&tools->forks[first]);
}



// void	eat(t_philo *philo)
// {
// 	t_tools	*tools;

// 	tools = philo->tools;
// 	pthread_mutex_lock(&tools->forks[philo->right_fork]);
// 	print_status(tools, philo->id, "has taken a fork");
// 	pthread_mutex_lock(&tools->forks[philo->left_fork]);
// 	print_status(tools, philo->id, "has taken a fork");
// 	print_status(tools, philo->id, "is eating");
// 	pthread_mutex_lock(&tools->meal);
// 	philo->last_meal = current_time();
// 	philo->meal_num++;
// 	pthread_mutex_unlock(&tools->meal);
// 	usleep(tools->eat_time * 1000);
// 	pthread_mutex_unlock(&tools->forks[philo->left_fork]);
// 	pthread_mutex_unlock(&tools->forks[philo->right_fork]);
// }

void	*life_cycle(void *arg)
{
	t_philo	*philo;
	t_tools	*tools;

	philo = (t_philo *)arg;
	tools = philo->tools;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!check_dead(tools) && tools->philo_num != 1)
	{
		eat(philo);
		pthread_mutex_lock(&tools->meal);
		if (tools->meal_num != -1 && philo->meal_num >= tools->meal_num)
		{
			pthread_mutex_unlock(&tools->meal);
			break ;
		}
		pthread_mutex_unlock(&tools->meal);
		print_status(tools, philo->id, "is sleeping");
		usleep(tools->sleep_time * 1000);
		print_status(tools, philo->id, "is thinking");
	}
	return (NULL);
}

void	ft_clean(t_tools *tools)
{
	int	i;

	i = 0;
	while (i < tools->philo_num)
	{
		pthread_join(tools->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < tools->philo_num)
	{
		pthread_mutex_destroy(&tools->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&tools->print);
	pthread_mutex_destroy(&tools->dead);
	pthread_mutex_destroy(&tools->meal);
	free(tools->forks);
	free(tools->philos);
}
