/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmathot <cmathot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:51:47 by cmathot           #+#    #+#             */
/*   Updated: 2024/05/14 13:45:41 by cmathot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	grododo(t_philo *philo, t_data *data)
{
	time_t	current;

	if (data->dead == 1)
		return ;
	current = get_time() - data->time_beginning;
	secure_print(MESS_SLEEP, current, philo->index, data);
	custom_sleep(data->time_to_sleep, data);
}

static void	think(t_philo *philo, t_data *data)
{
	time_t	current;

	if (data->dead == 1)
		return ;
	current = get_time() - data->time_beginning;
	secure_print(MESS_THINK, current, philo->index, data);
}

static void	eat(t_philo *philo, t_data *data)
{
	time_t	elapsed;

	pthread_mutex_lock(&data->forks[philo->left_fork]);
	elapsed = get_time() - data->time_beginning;
	secure_print(MESS_PICK_FORK, elapsed, philo->index, data);
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	elapsed = get_time() - data->time_beginning;
	secure_print(MESS_PICK_FORK, elapsed, philo->index, data);
	elapsed = get_time() - data->time_beginning;
	secure_print(MESS_EAT, elapsed, philo->index, data);
	philo->last_meal = elapsed;
	philo->meals++;
	custom_sleep(data->time_to_eat, data);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	philo->last_meal = data->time_beginning;
	if (philo->index % 2 == 0)
		custom_sleep(5, data);
	while (!data->dead)
	{
		eat(philo, data);
		if (philo->meals == data->n_meals)
			philo->is_full = 1;
		grododo(philo, data);
		think(philo, data);
	}
	return (NULL);
}
