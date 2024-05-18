/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:12:34 by lmoricon          #+#    #+#             */
/*   Updated: 2024/05/18 18:12:36 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_table *table)
{
	free(table->philos);
	free(table->threads);
	free(table->forks);
	free(table->forkflags);
}

void	destroy_mutexes(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->args.n_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
	}
	pthread_mutex_destroy(&table->write);
}

int	throw_error(char *str, t_table *table)
{
	printf("Error\t%s\n", str);
	destroy_mutexes(table);
	free_table(table);
	return (1);
}

int	ft_exit(t_table *table)
{
	destroy_mutexes(table);
	free_table(table);
	return (1);
}
