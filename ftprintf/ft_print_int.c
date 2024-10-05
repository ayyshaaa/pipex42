/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:02:58 by aistierl          #+#    #+#             */
/*   Updated: 2024/09/29 15:48:29 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

int	ft_int_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	if (n == INT_MIN)
		return (11);
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	ft_putnbr(int n)
{
	char	res;

	if (n == INT_MIN)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
	}
	res = n % 10 + '0';
	write(1, &res, 1);
}

int	ft_print_int(int number)
{
	ft_putnbr(number);
	return (ft_int_len(number));
}
