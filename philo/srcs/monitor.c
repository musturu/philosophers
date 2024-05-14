#include "philo.h"
#include <unistd.h>

void	kill_phil(t_table *table, int i);

void	check_health(void *tableu)
{
	int	i;
	t_table	*table;
	//long long startime;

	table = (t_table *)tableu;
	//startime = table->args.start_time;
	i = 0;
	while (1)
	{
		usleep(5);
		if (!table->philos[i].eat_flag && 
			millitime() >= table->philos[i].last_meal + table->args.tt_die)
			break ;
		i = (i + 1) % table->args.n_philos;
	}
	kill_phil(table,  i);
}

void	kill_phil(t_table *table, int i)
{
//	pthread_mutex_lock(table->philos[0].write);
	*table->philos[0].stop = 1;
	table->isdead = 1;
	printf("%lli %i MORTO, E' PROPRIO MORTO CREPATOAAAAAAAAAAA\n", millitime() - table->args.start_time, i + 1);
}
