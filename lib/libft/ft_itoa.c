/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:17:25 by ishenriq          #+#    #+#             */
/*   Updated: 2023/10/28 21:46:40 by ishenriq         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_decimal(int n)
{
	long	nb;
	int		sign;
	int		decimal;

	decimal = 0;
	sign = 0;
	nb = (long) n;
	if (nb < 0)
	{
		nb = -nb;
		sign++;
	}
	while (nb != 0)
	{
		nb = nb / 10;
		decimal++;
	}
	if (sign == 1)
		decimal++;
	if (decimal == 0)
		return (1);
	return (decimal);
}

static void	*ft_recursive_itoa(long n, char *result, int *i)
{
	if (n < 0)
	{
		result[(*i)++] = '-';
		n = -n;
	}
	if (n >= 10)
		ft_recursive_itoa(n / 10, result, i);
	result[(*i)++] = (n % 10) + 48;
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	char	*itoa;
	int		i;

	i = 0;
	n = (long) n;
	result = ft_calloc(ft_decimal(n) + 1, sizeof(char));
	if (result == 0)
		return (0);
	itoa = ft_recursive_itoa(n, result, &i);
	i = ft_decimal(n);
	*(itoa + i) = '\0';
	return (itoa);
}
