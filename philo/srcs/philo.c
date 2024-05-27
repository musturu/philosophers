/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:12:55 by lmoricon          #+#    #+#             */
/*   Updated: 2024/05/18 18:12:57 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_table	table;

	if (!validate(argc, argv))
		return (printf(BAD_ARGS));
	if (!initialize(argc, argv, &table))
		return (throw_error("Initializing", &table));
	if (run_threads(&table))
		return (throw_error("Threading", &table));
	ft_exit(&table);
	return (0);
}
