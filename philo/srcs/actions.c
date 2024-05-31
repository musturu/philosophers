/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:11:45 by lmoricon          #+#    #+#             */
/*   Updated: 2024/05/31 19:44:51 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

void	take_forks(t_phil *phil)
{
	if (phil->id % 2 == 0)
	{
		pthread_mutex_lock(phil->l_fork);
		*phil->lflag = 0;
		if (phil->args->n_philos == 1)
			return ;
		msg_lock("has taken a fork", phil->write, *phil);
		pthread_mutex_lock(phil->r_fork);
		*phil->rflag = 0;
		msg_lock("has taken a fork", phil->write, *phil);
	}
	else
	{
		pthread_mutex_lock(phil->r_fork);
		*phil->rflag = 0;
		msg_lock("has taken a fork", phil->write, *phil);
		if (phil->args->n_philos == 1)
			return ;
		pthread_mutex_lock(phil->l_fork);
		*phil->lflag = 0;
		msg_lock("has taken a fork", phil->write, *phil);
	}
}

void	drop_forks(t_phil *phil)
{
	*phil->lflag = 1;
	*phil->rflag = 1;
	pthread_mutex_unlock(phil->l_fork);
	pthread_mutex_unlock(phil->r_fork);
}

void	eat(t_phil *phil, int time_to_eat)
{
	if (phil->args->n_philos == 1)
		return ;
	pthread_mutex_lock(phil->deadlock);
	phil->eat_flag = 1;
	pthread_mutex_unlock(phil->deadlock);
	phil->last_meal = millitime();
	msg_lock("is eating", phil->write, *phil);
	phil->meals_count++;
	ft_usleep(time_to_eat);
	drop_forks(phil);
	phil->eat_flag = 0;
}

void	philo_sleep(t_phil *phil, int time_to_sleep)
{
	msg_lock("is sleeping", phil->write, *phil);
	ft_usleep(time_to_sleep);
}

void	eat_sleep_repeat(void *philo)
{
	t_phil	*phil;
	int		time_to_eat;
	int		time_to_sleep;

	phil = (t_phil *)philo;
	time_to_eat = phil->args->tt_eat;
	time_to_sleep = phil->args->tt_sleep;
	while (*phil->start == 0)
		continue ;
	phil->last_meal = millitime();
	if (phil->id % 2 == 0 || (phil->id == phil->args->n_philos && phil->args->n_philos % 2 == 1))
		ft_usleep(time_to_eat);
	while (!*(phil->stop))
	{
		take_forks(phil);
		eat(phil, time_to_eat);
		if (phil->args->n_philos == 1)
			break ;
		philo_sleep(phil, time_to_sleep);
		msg_lock("is thinking", phil->write, *phil);
		if (phil->args->n_philos % 2 == 1)
			ft_usleep(time_to_eat);
	}
}
