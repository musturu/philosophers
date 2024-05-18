/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:59:44 by lmoricon          #+#    #+#             */
/*   Updated: 2024/01/14 19:20:10 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned int	digitc(int n)
{
	unsigned int	count;

	count = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*aux_init(int n)
{
	char	*ret;

	if (n < 0)
		ret = (char *)malloc(sizeof(char) * (digitc(n) + 2));
	else
		ret = (char *)malloc(sizeof(char) * (digitc(n) + 1));
	if (ret == NULL)
		return (NULL);
	else
		return (ret);
}

static unsigned int	getpower(unsigned int count)
{
	unsigned int	i;

	i = 1;
	while (count > 1)
	{
		i *= 10;
		count--;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	ipwr;
	unsigned int	i;
	long int		longn;
	char			*ret;

	i = 0;
	ipwr = getpower(digitc(n));
	longn = n;
	ret = aux_init(n);
	if (ret == NULL)
		return (NULL);
	if (n < 0)
	{
		ret[i++] = '-';
		longn = -longn;
	}
	while (ipwr != 0)
	{
		ret[i++] = (longn / ipwr) + '0';
		longn %= ipwr;
		ipwr /= 10;
	}
	ret[i] = '\0';
	return (ret);
}
