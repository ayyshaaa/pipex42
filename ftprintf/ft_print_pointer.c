/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:08:01 by aistierl          #+#    #+#             */
/*   Updated: 2024/10/08 15:32:46 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

int	ft_hexa_lenp(unsigned long nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		nb /= 16;
		len++;
	}
	return (len);
}

void	ft_putnbr_hexap(unsigned long nb)
{
	char	res;

	if (nb > 15)
	{
		ft_putnbr_hexap(nb / 16);
		nb %= 16;
	}
	if (nb < 16 && nb > 9)
	{
		res = nb % 10 + 'a';
		write(1, &res, 1);
	}
	if (nb < 10)
	{
		res = nb % 10 + '0';
		write(1, &res, 1);
	}
}

int	ft_print_pointer(void *ptr)
{
	unsigned long	intptr;

	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	intptr = (unsigned long)ptr;
	write(1, "0x", 2);
	ft_putnbr_hexap(intptr);
	return (ft_hexa_lenp(intptr) + 2);
}
