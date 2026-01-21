/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmathot <cmathot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:16:48 by cmathot           #+#    #+#             */
/*   Updated: 2024/05/14 14:21:14 by cmathot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dump_truck(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->lock_dead);
	pthread_mutex_destroy(&data->lock_writing);
	if (data->philos)
		free(data->philos);
	if (data->forks)
	{
		while (i < data->n_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
}

void	*eating_alone(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(data->forks);
	secure_print(MESS_PICK_FORK, 0, 1, data);
	custom_sleep(data->time_to_die, data);
	secure_print(MESS_DEAD, data->time_to_die, 1, data);
	pthread_mutex_unlock(data->forks);
	return (NULL);
}

void	alone_routine(t_data *data)
{
	data->philos = malloc(sizeof(t_philo));
	data->forks = malloc(sizeof(t_mtx));
	if (!data->philos || !data->forks)
		return (dump_truck(data));
	if (pthread_mutex_init(data->forks, NULL))
		return (dump_truck(data));
	if (pthread_create(&data->philos->id, NULL, eating_alone, (void *)data))
		return (dump_truck(data));
	custom_sleep(data->time_to_die + 10, data);
	join_them_all(data, 1);
}

time_t	get_time(void)
{
	t_time	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
