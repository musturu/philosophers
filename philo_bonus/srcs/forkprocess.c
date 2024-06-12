/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkprocess.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:14:37 by lmoricon          #+#    #+#             */
/*   Updated: 2024/06/12 19:49:04 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

pid_t	forka(t_phil *phil, int i);

pid_t	*run_threads(t_table *table)
{
	int		i;
	pid_t	*pid;
	t_phil	phil;

	i = -1;
	pid = malloc(sizeof(pid_t) * table->args.n_philos);
	phil = init_philos(table);
	while (++i < table->args.n_philos)
	{
		pid[i] = forka(&phil, i);
	}
	return pid;
}

pid_t	forka(t_phil *phil, int i)
{
	pid_t	ret;

	ret = fork();
	if (!ret)
	{
		phil->id = i + 1;
		eat_sleep_repeat(phil);
		exit(0);
	}
	return ret;
}
