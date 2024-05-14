#include "philo.h"

void	take_forks(t_phil *phil)
{
	if (phil->id - 1 % 2 == 0)
	{
		pthread_mutex_lock(phil->r_fork);
		*phil->rflag = 1;
		msg_lock("has taken a fork", phil->write, *phil);
		pthread_mutex_lock(phil->l_fork);
		*phil->lflag = 1;
		msg_lock("has taken a fork", phil->write, *phil);
		return ;
	}
	else
	{
		pthread_mutex_lock(phil->l_fork);
		*phil->lflag = 1;
		msg_lock("has taken a fork", phil->write, *phil);
		pthread_mutex_lock(phil->r_fork);
		*phil->rflag = 1;
		msg_lock("has taken a fork", phil->write, *phil);
		return ;
	}
}

void	drop_forks(t_phil *phil)
{
	pthread_mutex_unlock(phil->l_fork);
	*phil->lflag = 0;
	pthread_mutex_unlock(phil->r_fork);
	*phil->rflag = 0;
}

void	eat(t_phil *phil, int time_to_eat)
{
	take_forks(phil);
	phil->last_meal = millitime();
	msg_lock("is eating", phil->write, *phil);
	phil->eat_flag = 1;
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
		if (*phil->rflag != 0 || *phil->lflag != 0)
			continue ;
		eat(phil, time_to_eat);
		philo_sleep(phil, time_to_sleep);
		msg_lock("is thinking", phil->write, *phil);
	}
}
