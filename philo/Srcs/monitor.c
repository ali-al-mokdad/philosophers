#include "../Include/philosophers.h"

int	check_dead(t_tools *tools)
{
	pthread_mutex_lock(&tools->dead);
	if (!tools->process)
	{
		pthread_mutex_unlock(&tools->dead);
		return (1);
	}
	pthread_mutex_unlock(&tools->dead);
	return (0);
}

int	monitor_meals(t_tools *tools)
{
	int	i;

	if (tools->meal_num == -1)
		return (0);
	i = -1;
	while (++i < tools->philo_num)
	{
		pthread_mutex_lock(&tools->meal);
		if (tools->philos[i].meal_num <= tools->meal_num)
		{
			pthread_mutex_unlock(&tools->meal);
			break ;
		}
		pthread_mutex_unlock(&tools->meal);
	}
	if (i == tools->philo_num)
	{
		pthread_mutex_lock(&tools->dead);
		tools->process = 0;
		pthread_mutex_unlock(&tools->dead);
		return (1);
	}
	return (0);
}

int	check_philo_dead(t_tools *tools, int i)
{
	pthread_mutex_lock(&tools->meal);
	if (tools->meal_num != -1
		&& tools->philos[i].meal_num >= tools->meal_num)
	{
		pthread_mutex_unlock(&tools->meal);
		return (0);
	}
	if (current_time() - tools->philos[i].last_meal >= tools->die_time)
	{
		pthread_mutex_unlock(&tools->meal);
		return (1);
	}
	pthread_mutex_unlock(&tools->meal);
	return (0);
}

int	monitor_dead(t_tools *tools)
{
	int	i;
	int	finished_meals;

	finished_meals = 0;
	i = 0;
	while (i < tools->philo_num)
	{
		pthread_mutex_lock(&tools->meal);
		if (tools->meal_num != -1
			&& tools->philos[i].meal_num >= tools->meal_num)
			finished_meals++;
		else if (current_time() - tools->philos[i].last_meal >= tools->die_time)
			return (pthread_mutex_unlock(&tools->meal),
				print_status(tools, i + 1, "died"),
				pthread_mutex_lock(&tools->dead), tools->process = 0,
				pthread_mutex_unlock(&tools->dead), 1);
		pthread_mutex_unlock(&tools->meal);
		i++;
	}
	if (tools->meal_num != -1 && finished_meals == tools->philo_num)
		return (pthread_mutex_lock(&tools->dead), tools->process = 0,
			pthread_mutex_unlock(&tools->dead), 1);
	return (0);
}

void	ft_monitor(t_tools *tools)
{
	while (1)
	{
		if (monitor_dead(tools) || monitor_meals(tools))
			break ;
	}
}
