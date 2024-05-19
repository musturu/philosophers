/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:11:45 by lmoricon          #+#    #+#             */
/*   Updated: 2024/05/18 18:12:39 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	take_forks(t_phil *phil)
{
	if (phil->id % 2 == 0)
	{
		pthread_mutex_lock(phil->l_fork);
		*phil->lflag = 0;
		msg_lock("has taken a r-fork", phil->write, *phil);
		if (phil->args.n_philos == 1)
			return ;
		pthread_mutex_lock(phil->r_fork);
		*phil->rflag = 0;
		msg_lock("has taken a l-fork", phil->write, *phil);
		phil->eat_flag = 1;
		return ;
	}
	else
	{
		pthread_mutex_lock(phil->r_fork);
		*phil->rflag = 0;
		msg_lock("has taken a l-fork", phil->write, *phil);
		if (phil->args.n_philos == 1)
			return ;
		pthread_mutex_lock(phil->l_fork);
		*phil->lflag = 0;
		msg_lock("has taken a r-fork", phil->write, *phil);
		phil->eat_flag = 1;
		return ;
	}
}

void	drop_forks(t_phil *phil)
{
	pthread_mutex_unlock(phil->l_fork);
	pthread_mutex_unlock(phil->r_fork);
	*phil->rflag = 1;
	*phil->lflag = 1;
}

void	eat(t_phil *phil, int time_to_eat)
{
	if (phil->args.n_philos == 1)
		return ;
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
	t_phil *phil;
	int		time_to_eat;
	int		time_to_sleep;

	phil = (t_phil *)philo;
	time_to_eat = phil->args.tt_eat;
	time_to_sleep = phil->args.tt_sleep;
	while (*phil->start == 0)
		continue ;
	while (!*(phil->stop))
	{
		usleep(30);
		take_forks(phil);
		eat(phil, time_to_eat);
		if (phil->args.n_philos == 1)
			break ;
		philo_sleep(phil, time_to_sleep);
		msg_lock("is thinking", phil->write, *phil);
	}
}
