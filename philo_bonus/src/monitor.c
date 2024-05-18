#include "philo.h"
#include <unistd.h>

void	kill_phil(t_phil *table);

void	check_health(void *phil)
{
	int	i;
	t_phil	*p;

	p = (t_phil *)phil;
	while (1)
	{
		if (( !p->eat_flag && millitime() >= p->last_meal + p->args.tt_die))
			break ;
		i = (i + 1) % p->args.n_philos;
	}
	kill_phil(p)  ;
}

void	kill_phil(t_phil *table)
{
	printf("%lli %i has died\n", millitime() - table->args.start_time, table->id);
	exit(0);
}
