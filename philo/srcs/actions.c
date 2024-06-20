/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:11:45 by lmoricon          #+#    #+#             */
/*   Updated: 2024/06/12 20:43:53 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_phil *phil)
{
	if (phil->id % 2 == 0)
	{
		pthread_mutex_lock(phil->l_fork);
		pthread_mutex_lock(phil->r_fork);
		msg_lock("has taken a fork\n", phil->write, *phil);
		return ;
	}
	else
	{
		pthread_mutex_lock(phil->r_fork);
		pthread_mutex_lock(phil->l_fork);
		msg_lock("has taken a fork\n", phil->write, *phil);
		return ;
	}
}

void	drop_forks(t_phil *phil)
{
	pthread_mutex_unlock(phil->l_fork);
	pthread_mutex_unlock(phil->r_fork);
}

void	eat(t_phil *phil, int time_to_eat)
{
	pthread_mutex_lock(phil->l_fork);
	pthread_mutex_lock(phil->r_fork);
	msg_lock("has taken a fork\n", phil->write, *phil);
	pthread_mutex_lock(phil->deadlock);
	phil->last_meal = millitime();
	phil->meals_count++;
	pthread_mutex_unlock(phil->deadlock);
	ft_usleep(time_to_eat);
	drop_forks(phil);
}

void	eat_sleep_repeat(void *philo)
{
	t_phil	*phil;
	int		time_to_eat;
	int		time_to_sleep;

	phil = (t_phil *)philo;
	time_to_eat = phil->args->tt_eat;
	time_to_sleep = phil->args->tt_sleep;
	while (!start_watch(phil))
		continue ;
	pthread_mutex_lock(phil->deadlock);
	phil->last_meal = millitime();
	pthread_mutex_unlock(phil->deadlock);
	if (phil->id % 2 == 0
		|| (phil->id == phil->args->n_philos && phil->args->n_philos % 2 == 1))
		ft_usleep(time_to_eat);
	while (!stop_watch(phil))
	{
		eat(phil, time_to_eat);
		msg_lock("is sleeping\n", phil->write, *phil);
		ft_usleep(time_to_sleep);
		msg_lock("is thinking\n", phil->write, *phil);
		if (phil->args->n_philos % 2 == 1)
			ft_usleep(time_to_eat);
	}
}
