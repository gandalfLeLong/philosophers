/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmathot <cmathot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:44:49 by cmathot           #+#    #+#             */
/*   Updated: 2024/05/15 13:26:18 by cmathot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	alloc_all(t_data *data)
{
	int	size;

	size = data->n_philos;
	data->philos = malloc (sizeof(t_philo) * size);
	if (!data->philos)
		return (-1);
	data->forks = malloc (sizeof(t_mtx) * size);
	if (!data->forks)
		return (-1);
	return (0);
}

static int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (-1);
		i++;
	}
	return (0);
}

static void	init_philos(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->n_philos)
	{
		philo = &data->philos[i];
		philo->index = i + 1;
		philo->meals = 0;
		philo->is_full = 0;
		philo->left_fork = i;
		philo->right_fork = i + 1;
		if (i == data->n_philos - 1)
			philo->right_fork = 0;
		philo->last_meal = 0;
		philo->data = data;
		i++;
	}
}

void	join_them_all(t_data *data, int nu)
{
	int		i;
	t_philo	*philo;

	i = 0;
	pthread_mutex_lock(&data->lock_dead);
	data->dead = 1;
	pthread_mutex_unlock(&data->lock_dead);
	while (i < nu)
	{
		philo = &data->philos[i];
		pthread_join(philo->id, NULL);
		i++;
	}
	dump_truck(data);
}

int	init_all(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	if (alloc_all(data) == -1)
		return (printf(ERR_MESS_MALLOC), -1);
	if (init_forks(data) == -1)
		return (printf(ERR_MESS_MTX_INIT), -1);
	data->time_beginning = get_time();
	init_philos(data);
	while (i < data->n_philos)
	{
		philo = &data->philos[i];
		if (pthread_create(&philo->id, NULL, routine, (void *)philo))
		{
			join_them_all(data, i);
			return (printf(ERR_MESS_THRD_CREAT), -1);
		}
		i++;
	}
	return (0);
}
