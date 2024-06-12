/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:13:08 by lmoricon          #+#    #+#             */
/*   Updated: 2024/06/12 15:48:40 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	if (count && size && (4294967295U / size <= count))
		return (0);
	ret = malloc(count * size);
	if (ret == NULL)
		return (NULL);
	memset(ret, 0, (count * size));
	return (ret);
}

long long	millitime(void)
{
	struct timeval	time;
	long long		microtime;

	gettimeofday(&time, NULL);
	microtime = time.tv_sec * 1000LL + time.tv_usec / 1000;
	return (microtime);
}

void	ft_usleep(useconds_t time)
{
	usleep(time * 200);
	usleep(time * 200);
	usleep(time * 200);
	usleep(time * 200);
	usleep(time * 199);
	return ;
}

void	msg_lock(char *str, pthread_mutex_t *lock, t_phil p)
{
	long long timestamp;

	pthread_mutex_lock(lock);
	timestamp = millitime() - p.args->start_time;
	if (!*p.stop)
	{
		printf("%llu %i %s", timestamp, p.id, str);
		if (str[0] == 'h')
			printf("%llu %i %s%llu %i %s", timestamp, p.id, str, timestamp, p.id, "is eating\n");
	}
	pthread_mutex_unlock(lock);
}

int	stop_watch(t_phil *phil)
{
	pthread_mutex_lock(phil->stopwatch);
	if (*phil->stop)
	{
		pthread_mutex_unlock(phil->stopwatch);
		return (1);
	}
	pthread_mutex_unlock(phil->stopwatch);
	return (0);
}
