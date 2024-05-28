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
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	kill_phil(t_table *table, int i, int flag);

char	has_to_die(t_table *t, int i, int end)
{
	if ((t->args.n_meals != 0 && end == t->args.n_meals)
		|| (!t->philos[i].eat_flag
			&& millitime() >= t->philos[i].last_meal + t->args.tt_die))
		return (1);
	return (0);
}

int	phil_checks(t_table *t, int i, int end)
{
	pthread_mutex_lock(t->deadlocks + i);
	if (has_to_die(t, i, end))
	{
		pthread_mutex_unlock(t->deadlocks + i);
		return (0);
	}
	pthread_mutex_unlock(t->deadlocks + i);
	if (t->args.n_meals != 0 && t->philos[i].meals_count >= t->args.n_meals)
		return (1);
	return (2);
}

void	check_health(void *tableu)
{
	int		i;
	t_table	*t;
	int		end;
	int		boole;

	t = (t_table *)tableu;
	while (1)
	{
		end = 0;
		i = -1;
		while (++i < t->args.n_philos)
		{
			boole = phil_checks(t, i, end);
			if (boole == 0)
				break ;
			else if (boole == 1)
				end++;
		}
		if ((t->args.n_meals != 0 && end == t->args.n_philos)
			|| i != t->args.n_philos)
			break ;
	}
	kill_phil(t, i, (t->args.n_meals != 0 && end == t->args.n_meals));
}

void	kill_phil(t_table *t, int i, int killflag)
{
	pthread_mutex_lock(t->philos[0].write);
	*t->philos[0].stop = 1;
	t->isdead = 1;
	if (!killflag)
		printf("%lli %i has died\n", millitime() - t->args.start_time, i + 1);
	else
		printf(GRNB"simulation has ended, no phils were harmed"RESET"\n");
	pthread_mutex_unlock(t->philos[0].write);
}
