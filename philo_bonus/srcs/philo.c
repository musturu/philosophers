/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:14:48 by lmoricon          #+#    #+#             */
/*   Updated: 2024/06/12 19:50:01 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_args(t_args args)
{
	printf("args;\n");
	printf("n_philos: %i\n", args.n_philos);
	printf("ttdie: %i\n", args.tt_die);
	printf("tteat: %i\n", args.tt_eat);
	printf("ttsleep: %i\n", args.tt_sleep);
	printf("nmeals: %i\n", args.n_meals);
	printf("start_time: %llu\n", args.start_time);
}

void	print_table(t_table table)
{
	print_args(table.args);
}

void	kill_children(t_table table, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < table.args.n_philos)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;
	pid_t	*pids;

	i = -1;
	if (!validate(argc, argv))
		return (printf(BAD_ARGS));
	if (!initialize(argc, argv, &table))
		return (throw_error("Initializing", &table));
	pids = run_threads(&table);
	while (++i < table.args.n_philos)
		sem_wait(table.stop);
	kill_children(table, pids);
	table.pid = pids;
	return (ft_exit(&table));
}
