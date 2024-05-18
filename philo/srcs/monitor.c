/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:12:51 by lmoricon          #+#    #+#             */
/*   Updated: 2024/05/18 18:12:53 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	kill_phil(t_table *table, int i, int flag);

void	check_health(void *tableu)
{
	int	i;
	t_table	*t;
	int	end;

	t = (t_table *)tableu;
	while (1)
	{
		end = 0;
		i = -1;
		while (++i < t->args.n_philos)
		{
			if ((t->args.n_meals != 0 && end == t->args.n_meals) 
				||	(!t->philos[i].eat_flag 
				&& millitime() >= t->philos[i].last_meal + t->args.tt_die))
				break ;
			if (t->args.n_meals != 0 && t->philos[i].meals_count >= t->args.n_meals)
				end++;
		}
		if ((t->args.n_meals != 0 && end == t->args.n_philos) 
			|| i != t->args.n_philos)
			break ;
	}
	kill_phil(t,  i, t->args.n_meals != 0 && end == t->args.n_philos);
}

void	kill_phil(t_table *table, int i, int killflag)
{
//	pthread_mutex_lock(table->philos[0].write);
	*table->philos[0].stop = 1;
	table->isdead = 1;
	if (!killflag)
		printf("%lli %i has died\n", millitime() - table->args.start_time, i + 1);
	else
		printf( GRNB"simulation has ended, no phils were harmed"reset"\n");
}
