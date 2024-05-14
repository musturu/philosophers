#include "philo.h"
#include <stdio.h>



/*void print_args(t_args args)
{
	printf("args;\n");
	printf("n_philos: %i\n", args.n_philos);
	printf("ttdie: %i\n", args.tt_die);
	printf("tteat: %i\n", args.tt_eat);
	printf("ttsleep: %i\n", args.tt_sleep);
	printf("nmeals: %i\n", args.n_meals);
	printf("start_time: %llu\n", args.start_time);
}*/

/*void	print_table(t_table table)
{
	int i;

	i = 0;
	print_args(table.args);
	while (i < table.args.n_philos)
	{
		printf("philo id %i\t rfork %p\t lfork %p\t write %p\t deadflag%p\n",
		table.philos[i].id, table.philos[i].r_fork, table.philos[i].l_fork, table.philos[i].write, table.philos[i].stop);
		i++;
	}
	printf("table write = %p\n" , &table.write);
}*/

int	main(int argc, char **argv)
{
	t_table table;

	if (!validate(argc, argv))
		return printf(BAD_ARGS);
	if (!initialize(argc, argv, &table))
		return throw_error("Initializing", &table);
	//print_table(table);
	if (run_threads(&table))
		return throw_error("Threading", &table);
	return (ft_exit(&table));
}
