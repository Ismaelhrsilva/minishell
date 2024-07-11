/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:17:01 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/11 16:46:40 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

long	ft_count(void)
{
	static long	count;

	return (count++);
}

void	ft_end_heredoc(int infile, const int std, char *gnl)
{
	(void ) gnl;
	close(infile);
	close(std);
}

void	ft_heredoc_sigint(char *gnl, const int std)
{
	if (g_status == SIGINT)
	{
		dup2(std, STDIN_FILENO);
		if (gnl)
		{
			free(gnl);
			gnl = NULL;
		}
	}
}

char	*ft_limiter(t_node *root, t_shell *shell)
{
	char	*limiter;
	char	*temp;

	limiter = ft_strdup(root->str);
	if (ft_count_chr(limiter, '\"') != 0
		|| ft_count_chr(limiter, '\'') != 0)
	{
		temp = limiter;
		limiter = ft_eliminate_signal(temp, shell);
		free(temp);
	}
	return (limiter);
}
