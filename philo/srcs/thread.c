/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:13:04 by lmoricon          #+#    #+#             */
/*   Updated: 2024/06/04 21:23:53 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	run_threads(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->args.n_philos)
	{
		if (pthread_create(&t->threads[i], NULL, (void *)&eat_sleep_repeat,
				&t->philos[i]))
			return (1);
		usleep(1);
	}
	pthread_mutex_lock(&t->stopwatch);
	t->args.start_time = millitime();
	t->start = 1;
	pthread_mutex_unlock(&t->stopwatch);
	if (pthread_create(&t->threads[i], NULL, (void *)&(check_health), t))
		return (1);
	while (i >= 0)
	{
		if (pthread_join(t->threads[i], NULL))
			return (1);
		i--;
	}
	return (0);
}
