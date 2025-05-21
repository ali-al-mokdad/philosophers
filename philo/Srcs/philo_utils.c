/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:15:13 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/05/21 16:15:13 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philosophers.h"

int	parse_arguments(int ac, char **av, t_tools *tools)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (write(2, "Error: Invalid argument\n", 24),
			exit(EXIT_FAILURE), 0);
	i = 1;
	while (i < ac)
	{
		if (!is_positive_digit(av[i]))
			return (write(2, "Error: Invalid argument\n", 24),
				exit(EXIT_FAILURE), 0);
		i++;
	}
	tools->philo_num = ft_atol(av[1]);
	tools->die_time = ft_atol(av[2]);
	tools->eat_time = ft_atol(av[3]);
	tools->sleep_time = ft_atol(av[4]);
	tools->process = 1;
	tools->ismeal = 0;
	tools->start_time = current_time();
	if (ac == 5)
		tools->meal_num = -1;
	else
		tools->meal_num = ft_atol(av[5]);
	return (1);
}

void	print_status(t_tools *tools, int id, char *message)
{
	pthread_mutex_lock(&tools->print);
	if (!check_dead(tools))
		printf("%ld %d %s\n",
			current_time() - tools->start_time, id, message);
	pthread_mutex_unlock(&tools->print);
}

void	setup_philo(t_tools *tools)
{
	int	i;

	i = 0;
	while (i < tools->philo_num)
	{
		tools->philos[i].id = i + 1;
		tools->philos[i].meal_num = 0;
		tools->philos[i].last_meal = current_time();
		tools->philos[i].tools = tools;
		tools->philos[i].left_fork = i;
		if (i == 0)
			tools->philos[i].right_fork = tools->philo_num - 1;
		else
			tools->philos[i].right_fork = i - 1;
		i++;
	}
}

void	setup_tools(t_tools *tools)
{
	int	i;

	tools->philos = (t_philo *)malloc(tools->philo_num * sizeof(t_philo));
	tools->forks = (pthread_mutex_t *)malloc(tools->philo_num
			* sizeof(pthread_mutex_t));
	i = 0;
	while (i < tools->philo_num)
	{
		pthread_mutex_init(&tools->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&tools->print, NULL);
	pthread_mutex_init(&tools->dead, NULL);
	pthread_mutex_init(&tools->meal, NULL);
	setup_philo(tools);
}
