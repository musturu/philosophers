#include "philo.h"

static t_args	init_args(int argc, char **argv);
static t_phil	*init_philos(t_table *table);

int	allocate(t_table *table)
{
	table->philos = malloc(sizeof(t_phil) * table->args.n_philos);
	table->threads = malloc(sizeof(pthread_t) * table->args.n_philos + 1);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->args.n_philos);
	table->forkflags = ft_calloc(sizeof(char) , table->args.n_philos);
	if (table->philos && table->threads && table->forks)
		return (1);
	else
		return 0;
}

int	initialize(int argc, char **argv, t_table *table)
{
	t_args			args;
	pthread_mutex_t	write;

	args = init_args(argc, argv);
	table->args = args;
	allocate(table);
	if (pthread_mutex_init(&write, NULL))
		return 0; //errore
	table->write = write;
	table->isdead = 0;
	table->start = 0;
	table->philos = init_philos(table);
	if (!table->philos)
		return 0;
	return (1);
}

static t_phil	*init_philos(t_table *table)
{
	int		i;
	t_phil	*philos;

	philos = table->philos;
	i = 0;
	while (i < table->args.n_philos)
	{
		philos[i].start = &(table->start);
		philos[i].args = table->args;
		philos[i].id = i + 1;
		philos[i].eat_flag = 0;
		philos[i].meals_count = 0;
		philos[i].last_meal = millitime();
		philos[i].stop = &(table->isdead);
		philos[i].write = &(table->write);
		philos[i].r_fork = table->forks + i;
		philos[i].rflag = table->forkflags + i;
		pthread_mutex_init(philos[i++].r_fork, NULL);
		philos[i % table->args.n_philos].l_fork = philos[i - 1].r_fork;
		philos[i % table->args.n_philos].lflag = philos[i - 1].rflag;
	}
	return (philos);
}

static t_args	init_args(int argc, char **argv)
{
	const int	philos = ft_atoi(argv[1]);
	const int	time_to_die = ft_atoi(argv[2]);
	const int	time_to_eat = ft_atoi(argv[3]);
	const int	time_to_sleep = ft_atoi(argv[4]);
	t_args ret;

	ret.tt_die = time_to_die;
	ret.tt_eat = time_to_eat;
	ret.n_philos = philos;
	ret.tt_sleep = time_to_sleep;
	ret.start_time = millitime();// + DELAY;
	if (argc >= 6)
		ret.n_meals = ft_atoi(argv[5]);
	else 
		ret.n_meals = 0;
	return (ret);
}
