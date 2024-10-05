/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:04:04 by aistierl          #+#    #+#             */
/*   Updated: 2024/09/29 15:48:45 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

int	ft_unsigned_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

void	ft_putnbr_unsigned(unsigned int nb)
{
	char	res;

	if (nb > 9)
		ft_putnbr_unsigned(nb / 10);
	res = nb % 10 + '0';
	write(1, &res, 1);
}

int	ft_print_unsigned(unsigned int number)
{
	ft_putnbr_unsigned(number);
	return (ft_unsigned_len(number));
}
