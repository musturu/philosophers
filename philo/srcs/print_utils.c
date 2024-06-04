/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:28:39 by lmoricon          #+#    #+#             */
/*   Updated: 2024/06/04 22:11:54 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
static void	ft_aux(long int num, int fd)
{
	int	w;

	if (num > 9)
		ft_aux(num / 10, fd);
	w = (num % 10) + '0';
	ft_putchar_fd(w, fd);
}
void	ft_putnbr_fd(int n, int fd)
{
	long int	num;

	num = n;
	ft_aux(num, fd);
}