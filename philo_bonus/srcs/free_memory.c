/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:14:40 by lmoricon          #+#    #+#             */
/*   Updated: 2024/05/18 18:14:40 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	sem_unlink("/stop");
	sem_unlink("/write");
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
