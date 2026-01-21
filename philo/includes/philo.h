/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmathot <cmathot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:45:14 by cmathot           #+#    #+#             */
/*   Updated: 2024/05/15 13:22:46 by cmathot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*-----INCLUDES-----*/
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/*-----DEFINES------*/
# define ERR_MESS_NB_ARGS "Error: wrong numbers of arguments\n"
# define ERR_MESS_ARGS "Error: wrong arguments\n"
# define ERR_MESS_MTX_INIT "Error: mutexs initilisation\n"
# define ERR_MESS_MALLOC "Error: malloc crashed\n"
# define ERR_MESS_THRD_CREAT "Error: issue during the thread initialistion\n"
# define MESS_PICK_FORK "%lld\t%d has taken a fork\n"
# define MESS_LEFT_FORK "%lld\t%d has left a fork\n"
# define MESS_EAT "%lld\t%d is eating\n"
# define MESS_THINK "%lld\t%d is thinking\n"
# define MESS_SLEEP "%lld\t%d is sleeping\n"
# define MESS_DEAD "%lld\t%d died\n"

typedef pthread_mutex_t	t_mtx;
typedef struct timeval	t_time;
typedef struct s_data	t_data;

/*------STRUCTURES-------*/
typedef struct s_atoi
{
	int	sign;
	int	res;
	int	tmp;
	int	flag;
}	t_atoi;

typedef struct s_philo
{
	pthread_t	id;
	int			index;
	int			meals;
	int			is_full;
	int			left_fork;
	int			right_fork;
	time_t		last_meal;
	t_data		*data;
}	t_philo;

struct s_data
{
	int			n_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			n_meals;
	int			dead;
	time_t		time_beginning;
	t_mtx		lock_dead;
	t_mtx		lock_writing;
	t_mtx		*forks;
	t_philo		*philos;
};

/*------FUNCTIONS------*/
//philo_utils.c
int		ft_atoi(char *str);
int		init_struct(t_data *data);
void	secure_print(char *mess, time_t time, int index, t_data *data);
void	dump_truck(t_data *data);
void	custom_sleep(time_t millisec, t_data *data);
void	dump_truck(t_data *data);
void	*eating_alone(void *arg);
void	alone_routine(t_data *data);
time_t	get_time(void);

//philo_init.c
int		init_all(t_data *data);
void	join_them_all(t_data *data, int nu);

//philo_routine.c
void	*routine(void *arg);

#endif
