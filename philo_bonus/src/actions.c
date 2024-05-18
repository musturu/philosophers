#include "philo.h"
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>

void	take_forks(t_phil *phil)
{
	sem_wait(phil->forks);
	printf("%llu %i took a fork\n", millitime() - phil->args.start_time, phil->id);
	sem_wait(phil->forks);
	printf("%llu %i took a fork\n", millitime() - phil->args.start_time, phil->id);
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
	printf("%llu %i is eating\n", millitime() - phil->args.start_time, phil->id);
	phil->eat_flag = 1;
	phil->meals_count++;
	ft_usleep(time_to_eat);
	drop_forks(phil);
	phil->eat_flag = 0;
}

void	philo_sleep(t_phil *phil, int time_to_sleep)
{
	printf("%llu %i is sleeping\n", millitime() - phil->args.start_time, phil->id);
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
	if (phil->forks == SEM_FAILED)
		exit(-1);
	pthread_create(&thread, NULL, (void *)check_health, phil);
	while (1)
	{
		eat(phil, time_to_eat);
		philo_sleep(phil, time_to_sleep);
	}
	sem_close(phil->forks);
	exit(1);
}
