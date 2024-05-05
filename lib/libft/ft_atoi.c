/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:12:43 by ishenriq          #+#    #+#             */
/*   Updated: 2023/10/30 21:16:36 by ishenriq         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

static int	ft_is_space(int c)
{
	return (c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v' || c == ' ');
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	minus;

	result = 0;
	minus = 0;
	nptr = (char *) nptr;
	while (ft_is_space(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			minus++;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	if (minus == 1)
		result = -result;
	return (result);
}
