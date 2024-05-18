#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <bits/pthreadtypes.h>
# include <time.h>
# include <string.h>
# include <semaphore.h>
# include <wait.h>
# include <stdlib.h>
# include <fcntl.h>

# define BAD_ARGS "Error\nuse: ./philo n_philos t_die t_sleep t_eat [n_meals]\n"
# define DELAY 500
# define GRNB "\e[42m"
# define CRES "\e[0m"
# define reset "\e[0m"
# define CRESET "\e[0m"

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
	char			*sem_name;
	char			eat_flag;
	long long		last_meal;
	t_args			args;
	int				meals_count;
	sem_t			*forks;
	sem_t			*write;
}	t_phil;

typedef struct s_table
{
	pid_t	*pid;
	t_args	args;
	t_phil	*philos;
	sem_t	*forks;
	sem_t	*write;
}	t_table;

int			ft_exit(t_table *table);
void		*ft_calloc(size_t count, size_t size);
int			ft_atoi(const char *str);
int			throw_error(char *str, t_table *table);
void		msg_lock(char *str, t_phil phil);
void		check_health(void *tableu);
int			validate(int argc, char **argv);
int			initialize(int argc, char **argv, t_table *table);
void		eat_sleep_repeat(void *philo);
int			run_threads(t_table *table);
int			ft_usleep(useconds_t time);
long long	millitime(void);
char		*ft_itoa(int n);

#endif
