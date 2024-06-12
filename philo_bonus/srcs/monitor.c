/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:14:45 by lmoricon          #+#    #+#             */
/*   Updated: 2024/06/12 20:09:16 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <semaphore.h>
#include <unistd.h>

void	kill_phil(t_phil *table);

void	check_health(void *phil)
{
	t_phil	*p;

	p = (t_phil *)phil;
	while (1)
	{
		sem_wait(p->data);
		if ((millitime() > p->last_meal + p->args.tt_die + 3))
			break ;
		sem_post(p->data);
	}
	kill_phil(p);
	return ;
}

void	kill_phil(t_phil *table)
{
	int	i;

	i = -1;
	msg_lock("died", table->write, *table);
	while (++i < table->args.n_philos)
		sem_post(table->stop);
}
