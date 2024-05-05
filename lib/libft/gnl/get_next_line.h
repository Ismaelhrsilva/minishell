/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:21:26 by ishenriq          #+#    #+#             */
/*   Updated: 2024/01/03 20:17:52 by ishenriq         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_listg
{
	char			content;
	struct s_listg	*next;
}	t_listg;

char	*get_next_line(int fd);
t_listg	*gnl_lstnew(void *content);
t_listg	*gnl_lstlast(t_listg *lst);
void	gnl_lstadd_back(t_listg **lst, t_listg *new);
int		gnl_lstsize(t_listg *lst);

#endif
