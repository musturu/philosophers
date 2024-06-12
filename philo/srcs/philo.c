/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:12:55 by lmoricon          #+#    #+#             */
/*   Updated: 2024/06/12 16:05:53 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_table	table;

	if (!validate(argc, argv))
		return (printf(BAD_ARGS));
	if (ft_atoi(argv[1]) == 1)
		return (printf("0 1 has died\n"));
	if (!initialize(argc, argv, &table))
		return (throw_error("Initializing", &table));
	if (run_threads(&table))
		return (throw_error("Threading", &table));
	ft_exit(&table);
	return (0);
}
