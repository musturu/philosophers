#include "philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	if (count && size && (4294967295U / size <= count))
		return (0);
	ret = malloc(count * size);
	if (ret == NULL)
		return (NULL);
	memset(ret, 0,(count * size));
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

	start = millitime();
	while ((millitime() - start) < time)
		usleep(time / 10);
	return (0);
}
