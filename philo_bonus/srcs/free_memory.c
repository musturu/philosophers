/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:14:40 by lmoricon          #+#    #+#             */
/*   Updated: 2024/06/12 19:49:36 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <semaphore.h>

void	destroy_sem(void)
{
	sem_unlink("/forks");
	sem_unlink("/stop");
	sem_unlink("/write");
	sem_unlink("/data");
	sem_unlink("/greenflag");
	sem_unlink("/stopmain");
}

void	close_sems(t_phil	phil)
{
	sem_close(phil.write);
	sem_close(phil.data);
	sem_close(phil.stop);
	sem_close(phil.forks);
	sem_close(phil.greenflag);
	sem_close(phil.stopmain);
}

int	throw_error(char *str, t_table *table)
{
	printf("Error\t%s\n", str);
	destroy_sem();
	close_sems(table->philos);
	exit (1);
	return (1);
}

int	ft_exit(t_table *table)
{
	destroy_sem();
	close_sems(table->philos);
	free(table->pid);
	return (1);
}
