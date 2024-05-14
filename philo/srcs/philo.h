#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <bits/pthreadtypes.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>

# define BAD_ARGS "Error\nuse: ./philo n_philos t_die t_sleep t_eat [n_meals]\n"
# define DELAY 500

typedef struct s_args
{
	int			n_philos;
	int			tt_die;
	int			tt_sleep;
	int			tt_eat;
	int			n_meals;
	long long	start_time;
}	t_args;

typedef struct s_philo
{
	int				id;
	char			eat_flag;
	long long		last_meal;
	t_args			args;
	int				meals_count;
	int				*start;
	int				*stop;
	pthread_mutex_t	*write;
	pthread_mutex_t	*r_fork;
	char			*rflag;
	char			*lflag;
	pthread_mutex_t	*l_fork;
}	t_phil;

typedef struct s_table
{
	int				isdead;
	int				start;
	t_args			args;
	t_phil			*philos;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	char			*forkflags;
	pthread_mutex_t	write;
}	t_table;

int			ft_exit(t_table *table);
void		*ft_calloc(size_t count, size_t size);
int			ft_atoi(const char *str);
int			throw_error(char *str, t_table *table);
void		msg_lock(char *str, pthread_mutex_t *lock, t_phil phil);
void		check_health(void *tableu);
int			validate(int argc, char **argv);
int			initialize(int argc, char **argv, t_table *table);
void		eat_sleep_repeat(void *philo);
int			run_threads(t_table *table);
int			ft_usleep(useconds_t time);
long long	millitime(void);

#endif
