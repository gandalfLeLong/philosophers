/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmathot <cmathot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:20:07 by cmathot           #+#    #+#             */
/*   Updated: 2024/05/14 14:20:52 by cmathot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_atoi(char *str)
{
	t_atoi	data;

	data.res = 0;
	data.sign = 1;
	data.flag = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			data.sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		data.flag = 1;
		data.tmp = data.res;
		data.res = (data.res * 10) + *str - '0';
		if (data.tmp > data.res)
			return (-1);
		str++;
	}
	if (!data.flag)
		return (-1);
	return (data.res * data.sign);
}

void	secure_print(char *mess, time_t time, int index, t_data *data)
{
	if (data->dead == 1)
		return ;
	pthread_mutex_lock(&data->lock_writing);
	printf(mess, time, index);
	pthread_mutex_unlock(&data->lock_writing);
}

int	init_struct(t_data *data)
{
	data->n_philos = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->n_meals = -1;
	data->dead = 0;
	data->time_beginning = 0;
	if (pthread_mutex_init(&data->lock_writing, NULL))
		return (printf("%s", ERR_MESS_MTX_INIT), -1);
	if (pthread_mutex_init(&data->lock_dead, NULL))
	{
		pthread_mutex_destroy(&data->lock_writing);
		return (printf("%s", ERR_MESS_MTX_INIT), -1);
	}
	data->philos = NULL;
	data->forks = NULL;
	return (0);
}

void	custom_sleep(time_t millisec, t_data *data)
{
	time_t	start;

	start = get_time();
	while (!data->dead)
	{
		if (get_time() - start >= millisec)
			break ;
		usleep(2 * data->n_philos);
	}
}
