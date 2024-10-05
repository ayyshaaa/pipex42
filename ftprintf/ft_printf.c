/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:42:06 by aistierl          #+#    #+#             */
/*   Updated: 2024/09/29 15:48:50 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

int	ft_comp_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_isalpha(int c)
{
	int	lett;

	lett = c % 256;
	if ((lett >= 65 && lett <= 90) || (lett >= 97 && lett <= 122))
		return (1);
	else
		return (0);
}

int	ft_print_spe(const char format, va_list extra)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += ft_print_char(va_arg(extra, unsigned int));
	else if (format == 's')
		count += ft_print_string(va_arg(extra, const char *));
	else if (format == 'i' || format == 'd')
		count += ft_print_int(va_arg(extra, int));
	else if (format == 'u')
		count += ft_print_unsigned(va_arg(extra, unsigned int));
	else if (format == 'X' || format == 'x')
		count += ft_print_hexa(va_arg(extra, unsigned int), format);
	else if (format == 'p')
		count += ft_print_pointer(va_arg(extra, void *));
	else if (format == '%')
		count += ft_print_char('%');
	return (count);
}

int	ft_printf(const char *s, ...)
{
	va_list	extra;
	int		count;

	count = 0;
	if (!s)
		return (-1);
	va_start(extra, s);
	while (*s != '\0')
	{
		if (*s == '%')
		{
			s++;
			if (ft_comp_set(*s, "cspdiuxX\%") == 1)
				count += ft_print_spe(*s, extra);
			else if (ft_isalpha(*s) == 1)
				return ((count += ft_print_char('%') + ft_print_string(s++)));
			else
				return (-1);
		}
		else
			count += ft_print_char(*s);
		s++;
	}
	va_end(extra);
	return (count);
}
