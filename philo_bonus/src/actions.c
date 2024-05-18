/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:14:33 by lmoricon          #+#    #+#             */
/*   Updated: 2024/05/18 18:14:34 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

void	take_forks(t_phil *phil)
{
	sem_wait(phil->forks);
	msg_lock("took a fork", phil->write, *phil);
	sem_wait(phil->forks);
	msg_lock("took a fork", phil->write, *phil);
}

void	drop_forks(t_phil *phil)
{
	sem_post(phil->forks);
	sem_post(phil->forks);
}

void	eat(t_phil *phil, int time_to_eat)
{
	take_forks(phil);
	phil->last_meal = millitime();
	msg_lock("is eating", phil->write, *phil);
	phil->eat_flag = 1;
	phil->meals_count++;
	if (phil->meals_count == phil->args.n_meals)
		sem_post(phil->stop);
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
	t_phil		*phil;
	int			time_to_eat;
	int			time_to_sleep;
	pthread_t	thread;

	phil = (t_phil *)philo;
	printf("philo number %i has entered the cycle\n", phil->id);
	time_to_eat = phil->args.tt_eat;
	time_to_sleep = phil->args.tt_sleep;
	phil->forks = sem_open("/forks", 0);
	phil->stop = sem_open("/stop", 0);
	phil->write = sem_open("/write", 0);
	if (phil->forks == SEM_FAILED || phil->write == SEM_FAILED 
		|| phil->stop == SEM_FAILED)
		exit(-1);
	pthread_create(&thread, NULL, (void *)check_health, phil);
	while (1)
	{
		eat(phil, time_to_eat);
		philo_sleep(phil, time_to_sleep);
		msg_lock("is thinking", phil->write, *phil);
	}
	pthread_join(thread, NULL);
	sem_close(phil->write);
	sem_close(phil->stop);
	sem_close(phil->forks);
	exit(1);
}
