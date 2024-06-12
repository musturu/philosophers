/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:14:58 by lmoricon          #+#    #+#             */
/*   Updated: 2024/06/12 19:42:41 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <semaphore.h>
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

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;

	usleep(time * 500);
	usleep(time * 500);
	return (0);
	start = millitime();
	while ((millitime() - start) < time)
		usleep(time / 10);
	return (0);
}

void	msg_lock(char *str, sem_t *lock, t_phil phil)
{
	long long	timestamp;

	sem_wait(lock);
	timestamp = millitime() - phil.args.start_time;
	printf("%llu %i %s\n", timestamp, phil.id, str);
	if (str[0] == 'h')
	{
		printf("%llu %i %s\n", timestamp, phil.id, str);
		printf("%llu %i %s\n", timestamp, phil.id, "is eating");
	}
	if (str[0] != 'd')
		sem_post(lock);
}
