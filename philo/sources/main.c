/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmathot <cmathot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:26:09 by cmathot           #+#    #+#             */
/*   Updated: 2024/05/15 13:23:03 by cmathot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_meal_time(t_data *data, t_philo *philo)
{
	time_t	current;
	time_t	elapsed;

	current = get_time() - data->time_beginning;
	elapsed = current - philo->last_meal;
	if (elapsed > data->time_to_die)
	{
		pthread_mutex_lock(&data->lock_dead);
		secure_print(MESS_DEAD, current, philo->index, data);
		data->dead = 1;
		pthread_mutex_unlock(&data->lock_dead);
		return (1);
	}
	return (0);
}

static int	check_meals_number(t_data *data, char *tab_full, int i)
{
	if (data->philos[i].is_full)
		tab_full[i] = 1;
	i = 0;
	while (i < data->n_philos)
	{
		if (tab_full[i] == 0)
			return (0);
		i++;
	}
	pthread_mutex_lock(&data->lock_dead);
	data->dead = 1;
	pthread_mutex_unlock(&data->lock_dead);
	return (1);
}

static void	watching_threads(t_data *data)
{
	int		i;
	int		count_full;
	char	*tab_full;

	count_full = 0;
	tab_full = malloc(sizeof(int) * (data->n_philos));
	tab_full = memset(tab_full, 0, data->n_philos);
	if (!tab_full)
	{
		printf(ERR_MESS_MALLOC);
		return ;
	}
	while (data->dead == 0)
	{
		i = 0;
		while (i < data->n_philos)
		{
			if (check_meal_time(data, &data->philos[i]))
				break ;
			if (check_meals_number(data, tab_full, i))
				break ;
			i++;
		}
	}
	free(tab_full);
}

static int	parsing_data(int ac, char **av, t_data *data)
{
	if (ac < 5 || ac > 6)
		return (printf("%s", ERR_MESS_NB_ARGS), -1);
	data->n_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->n_meals = ft_atoi(av[5]);
		if (data->n_meals <= 0)
			return (printf("%s", ERR_MESS_ARGS), -1);
	}
	if (data->n_philos <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0)
		return (printf("%s", ERR_MESS_ARGS), -1);
	if (data->time_to_sleep <= 0 || data->n_philos > 200)
		return (printf("%s", ERR_MESS_ARGS), -1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (init_struct(&data) == -1)
		return (1);
	if (parsing_data(ac, av, &data) == -1)
		return (dump_truck(&data), 2);
	if (data.n_philos == 1)
		return (alone_routine(&data), 0);
	if (init_all(&data) == -1)
		return (dump_truck(&data), 3);
	custom_sleep(10, &data);
	watching_threads(&data);
	join_them_all(&data, data.n_philos);
	return (0);
}
