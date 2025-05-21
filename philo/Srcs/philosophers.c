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

void	eat(t_philo *philo)
{
	t_tools	*tools;

	tools = philo->tools;
	pthread_mutex_lock(&tools->forks[philo->right_fork]);
	print_status(tools, philo->id, "has taken a fork");
	pthread_mutex_lock(&tools->forks[philo->left_fork]);
	print_status(tools, philo->id, "has taken a fork");
	print_status(tools, philo->id, "is eating");
	pthread_mutex_lock(&tools->meal);
	philo->last_meal = current_time();
	philo->meal_num++;
	pthread_mutex_unlock(&tools->meal);
	usleep(tools->eat_time * 1000);
	pthread_mutex_unlock(&tools->forks[philo->left_fork]);
	pthread_mutex_unlock(&tools->forks[philo->right_fork]);
}

void	*life_cycle(void *arg)
{
	t_philo	*philo;
	t_tools	*tools;

	philo = (t_philo *)arg;
	tools = philo->tools;
	if (philo->id % 2 == 0)
		usleep(1500);
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
