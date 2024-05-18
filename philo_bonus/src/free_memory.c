#include "philo.h"
#include <semaphore.h>

void	free_table(t_table *table)
{
	free(table->philos);
	free(table->pid);
}

void	destroy_sem()
{
	sem_unlink("/forks");
}

int	throw_error(char *str, t_table *table)
{
	printf("Error\t%s\n", str);
	destroy_sem();
	free_table(table);
	exit (1);
	return (1);
}

int	ft_exit(t_table *table)
{
	sem_close(table->forks);
	destroy_sem();
	free_table(table);
	return (1);
}
