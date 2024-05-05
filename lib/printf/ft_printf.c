/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:59:53 by ishenriq          #+#    #+#             */
/*   Updated: 2023/11/27 20:22:44 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_content(va_list variadic_list, char content)
{
	int	count;

	count = 0;
	if (content == 'c')
		count += ft_putchar(va_arg(variadic_list, int));
	else if (content == 's')
		count += ft_putstr(va_arg(variadic_list, char *));
	else if (content == 'p')
		count += ft_point_voidhex(va_arg(variadic_list, unsigned long int));
	else if (content == 'd')
		count += ft_putnmb(va_arg(variadic_list, int), 10, content);
	else if (content == 'i')
		count += ft_putnmb(va_arg(variadic_list, int), 10, content);
	else if (content == 'u')
		count += ft_putnmb(va_arg(variadic_list, unsigned int), 10, content);
	else if (content == 'x')
		count += ft_putnmb_hex(va_arg(variadic_list, unsigned int), content);
	else if (content == 'X')
		count += ft_putnmb_hex(va_arg(variadic_list, int), content);
	else
		count += write(1, &content, 1);
	return (count);
}

int	ft_printf(const char *content, ...)
{
	va_list	variadic_list;
	int		count;

	count = 0;
	va_start(variadic_list, content);
	while (*content)
	{
		if (*content != '%')
			count += write(1, content, 1);
		else
		{
			if (*content == '\0')
				return (1);
			count += print_content(variadic_list, *(++content));
		}
		++content;
	}
	va_end(variadic_list);
	return (count);
}
