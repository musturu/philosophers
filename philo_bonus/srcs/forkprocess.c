/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkprocess.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:14:37 by lmoricon          #+#    #+#             */
/*   Updated: 2024/06/06 21:20:24 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <math.h>
#include <unistd.h>

int	run_threads(t_table *table)
{
	int		i;
	pid_t	*pid;

	i = -1;
	pid = malloc(sizeof(pid_t) * table->args.n_philos);
	if (!pid)
		return (1);
	while (++i < table->args.n_philos)
	{
		pid[i] = fork();
		if (!pid[i])
		{
			eat_sleep_repeat(table->philos + i);
			exit(0);
		}
	}
	table->pid = pid;
	return (0);
}
