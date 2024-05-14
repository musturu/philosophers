#include "philo.h"

int	run_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->args.n_philos)
	{
		if (pthread_create(&table->threads[i], NULL, (void *)&eat_sleep_repeat,
					 &table->philos[i]))
			return 1;
		printf("thread #%i started\n", i);
		usleep(1);
	}
	if (pthread_create(&table->threads[i], NULL, (void *)&(check_health), table))
		return 1;
	i = -1;
	table->start = 1;
	while (++i <= table->args.n_philos)
	{
		if (pthread_join(table->threads[i], NULL))
			return 1;
	}
	printf("run_threads_end\n");
	return (0);
}
