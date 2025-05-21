/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:15:29 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/05/21 16:15:29 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	long			id;
	long			last_meal;
	long			meal_num;
	pthread_t		thread;
	struct s_tools	*tools;
	int				right_fork;
	int				left_fork;
}	t_philo;

typedef struct s_tools
{
	long			philo_num;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			meal_num;
	long			start_time;
	int				process;
	int				ismeal;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	meal;
}	t_tools;

// Utils
long	current_time(void);
long	ft_atol(const char *str);
int		ft_isdigit(char c);
int		ft_isspace(char c);
int		is_positive_digit(char *str);

// Initialization
void	setup_tools(t_tools *tools);
void	setup_philo(t_tools *tools);

// Lifecycle
void	*life_cycle(void *arg);
void	eat(t_philo *philo);

// Monitoring
void	ft_monitor(t_tools *tools);
int		monitor_meals(t_tools *tools);
int		monitor_dead(t_tools *tools);
int		check_philo_dead(t_tools *tools, int i);
int		check_dead(t_tools *tools);

// Execution
void	ft_philosophers(t_tools *tools);
void	print_status(t_tools *tools, int id, char *message);
void	ft_clean(t_tools *tools);

// Parsing
int		parse_arguments(int ac, char **av, t_tools *tools);

#endif
