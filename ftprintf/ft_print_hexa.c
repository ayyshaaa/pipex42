/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:46:39 by aistierl          #+#    #+#             */
/*   Updated: 2024/09/29 15:48:22 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

int	ft_hexa_len(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 16;
		len++;
	}
	return (len);
}

void	ft_putnbr_hexa(unsigned int number, char type)
{
	char	res;

	if (number > 15)
	{
		ft_putnbr_hexa(number / 16, type);
		number %= 16;
	}
	if (number < 16 && number > 9 && type == 'X')
	{
		res = number % 10 + 'A';
		write(1, &res, 1);
	}
	if (number < 16 && number > 9 && type == 'x')
	{
		res = number % 10 + 'a';
		write(1, &res, 1);
	}
	if (number >= 0 && number <= 9)
	{
		res = number % 10 + '0';
		write(1, &res, 1);
	}
}

int	ft_print_hexa(unsigned int nb, char type)
{
	ft_putnbr_hexa(nb, type);
	return (ft_hexa_len(nb));
}
