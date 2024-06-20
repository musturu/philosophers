/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:14:33 by lmoricon          #+#    #+#             */
/*   Updated: 2024/06/12 20:22:20 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

void	eat(t_phil *phil, int time_to_eat)
{
	sem_wait(phil->forks);
	sem_wait(phil->forks);
	msg_lock("has taken a fork", phil->write, *phil);
	sem_wait(phil->data);
	phil->last_meal = millitime();
	sem_post(phil->data);
	phil->meals_count++;
	if (phil->meals_count == phil->args.n_meals)
		sem_post(phil->stop);
	ft_usleep(time_to_eat);
	sem_post(phil->forks);
	sem_post(phil->forks);
}

void	philo_sleep(t_phil *phil, int time_to_sleep)
{
	msg_lock("is sleeping", phil->write, *phil);
	ft_usleep(time_to_sleep);
}

void	eat_sleep_repeat(void *philo)
{
	t_phil		*phil;
	int			time_to_eat;
	int			time_to_sleep;
	pthread_t	thread;

	phil = (t_phil *)philo;
	time_to_eat = phil->args.tt_eat;
	time_to_sleep = phil->args.tt_sleep;
	phil->last_meal = millitime();
	phil->thread = thread;
	pthread_create(&thread, NULL, (void *)check_health, phil);
	pthread_detach(thread);
	while (1)
	{
		eat(phil, time_to_eat);
		msg_lock("is sleeping", phil->write, *phil);
		ft_usleep(time_to_sleep);
		msg_lock("is thinking", phil->write, *phil);
		if (phil->args.n_philos % 2 == 1)
			ft_usleep(time_to_eat);
	}
}
