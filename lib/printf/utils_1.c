/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:27:49 by ishenriq          #+#    #+#             */
/*   Updated: 2023/12/16 19:18:13 by ishenriq         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	int	count;

	count = 0;
	count += write(1, &c, 1);
	return (count);
}

int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (*str != '\0')
	{
		ft_putchar((int) *str);
		++count;
		++str;
	}
	return (count);
}

int	ft_strlen_p(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_count_digits(size_t n, int base_lenght)
{
	unsigned int	digits;

	if (n == 0)
		return (1);
	digits = 0;
	while (n > 0)
	{
		digits++;
		n /= base_lenght;
	}
	return (digits);
}

char	*ft_ulitohex(unsigned long int n, char *base_str)
{
	unsigned long int	int_to_hex;
	size_t				digits;
	int					base_lenght;
	char				*result;

	base_lenght = ft_strlen_p(base_str);
	int_to_hex = n;
	digits = ft_count_digits(n, base_lenght);
	result = malloc(digits + 1);
	if (!result)
		return (0);
	result[digits--] = '\0';
	while (int_to_hex > 0)
	{
		result[digits--] = base_str[int_to_hex % base_lenght];
		int_to_hex /= base_lenght;
	}
	if (digits == 0 && result[1] == '\0')
		result[0] = '0';
	return (result);
}
