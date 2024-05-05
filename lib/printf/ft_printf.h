/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:56:25 by ishenriq          #+#    #+#             */
/*   Updated: 2023/12/16 19:19:57 by ishenriq         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int				ft_printf(const char *content, ...);
int				ft_putchar(char c);
int				ft_putstr(char *str);
int				ft_putnmb(long nb, int base, char content);
int				ft_strlen_p(char *str);
size_t			ft_count_digits(size_t n, int base_lenght);
char			*ft_ulitohex(unsigned long int n, char *base_str);
char			*ft_uitohex(unsigned int n, char *base_str);
int				ft_point_voidhex(unsigned long int str);
unsigned int	ft_putnmb_hex(unsigned int nb, char content);

#endif
