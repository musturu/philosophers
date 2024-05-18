#include "philo.h"

static t_args	init_args(int argc, char **argv);
static t_phil	*init_philos(t_table *table);

int	allocate(t_table *table)
{
	int i = - 1;

	table->philos = malloc(sizeof(t_phil) * table->args.n_philos);
	if (!table->philos)
		return (0);
	table->forks = sem_open("/forks", O_CREAT, 0777 , 0U);
	table->stop = sem_open("/stop", O_CREAT, 0777 , 0U);
	table->write = sem_open("/write", O_CREAT, 0777 , 0U);
	if (table->forks == SEM_FAILED || table->write == SEM_FAILED 
		|| table->stop == SEM_FAILED)
		return (0);
	sem_post(table->write);
	while (++i < table->args.n_philos)
		sem_post(table->forks);
	return (1);
}

int	initialize(int argc, char **argv, t_table *table)
{
	t_args			args;

	args = init_args(argc, argv);
	table->args = args;
	if (!allocate(table))
		return (0);
	table->philos = init_philos(table);
	return (1);
}

static t_phil	*init_philos(t_table *table)
{
	int		i;
	t_phil	*philos;

	philos = table->philos;
	i = -1;
	while (++i < table->args.n_philos)
	{
		philos[i].args = table->args;
		philos[i].id = i + 1;
		philos[i].eat_flag = 0;
		philos[i].meals_count = 0;
		philos[i].last_meal = millitime();
	}
	return (philos);
}

static t_args	init_args(int argc, char **argv)
{
	const int	philos = ft_atoi(argv[1]);
	const int	time_to_die = ft_atoi(argv[2]);
	const int	time_to_eat = ft_atoi(argv[3]);
	const int	time_to_sleep = ft_atoi(argv[4]);
	t_args		ret;

	ret.tt_die = time_to_die;
	ret.tt_eat = time_to_eat;
	ret.n_philos = philos;
	ret.tt_sleep = time_to_sleep;
	ret.start_time = millitime();
	if (argc >= 6)
		ret.n_meals = ft_atoi(argv[5]);
	else
		ret.n_meals = 0;
	return (ret);
}
