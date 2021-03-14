/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:15:42 by nidescre          #+#    #+#             */
/*   Updated: 2019/11/05 17:14:57 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	core_putnbr(long n, int size, int fd, long pow)
{
	int		i;
	char	c;

	i = 0;
	while (i < size)
	{
		c = (char)(n / pow) + 48;
		write(fd, &c, 1);
		n = n % pow;
		pow /= 10;
		i++;
	}
}

void			ft_putnbr_fd(int n, int fd)
{
	long	pow;
	int		size;
	long	nb;

	size = 0;
	nb = n;
	pow = 1;
	if (n == 0)
		write(fd, "0", 1);
	if (n < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	while (nb / pow)
	{
		pow *= 10;
		size++;
	}
	pow /= 10;
	core_putnbr(nb, size, fd, pow);
}
