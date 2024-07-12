/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:17:01 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/11 21:01:37 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

char	*expand_heredoc(char *gnl, t_node *root, t_shell *shell)
{
	char	*gnl_temp;

	if (ft_count_chr(root->str_not_expanded, '\'') == 0
		&& ft_count_chr(root->str_not_expanded, '\"') == 0)
	{
		gnl_temp = gnl;
		gnl = ft_parse_expand_heredoc(gnl, shell);
		free(gnl_temp);
	}
	return (gnl);
}

void	write_heredoc(char *gnl, int infile)
{
	char	*gnl_temp;

	if (ft_strncmp(gnl, "0x1A", 4) != 0)
	{
		gnl_temp = gnl;
		gnl = ft_strjoin(gnl, "\n");
		free(gnl_temp);
		ft_putstr_fd(gnl, infile);
		free(gnl);
	}
	else if (gnl)
		free(gnl);
}

char	*read_heredoc(t_node *root, t_shell *shell, int infile)
{
	char	*gnl;
	char	*limiter;

	g_status = 0;
	while (1)
	{
		status_here(HERE_DOC, 1);
		gnl = readline("> ");
		status_here(HERE_DOC, 0);
		if (g_status == SIGINT || (gnl == NULL && g_status != SIGINT))
			break ;
		limiter = ft_limiter(root, shell);
		if (gnl && ft_strncmp(gnl, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(limiter) == ft_strlen(gnl))
		{
			free(limiter);
			break ;
		}
		gnl = expand_heredoc(gnl, root, shell);
		write_heredoc(gnl, infile);
		free(limiter);
	}
	return (gnl);
}

char	*ft_heredoc(t_node *root, t_shell *shell)
{
	char		*gnl;
	char		*temp_n;
	int			infile;
	char		*itoa_count;

	itoa_count = ft_itoa(ft_count());
	temp_n = ft_strjoin(TEMP, itoa_count);
	free(itoa_count);
	infile = open(temp_n, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	gnl = read_heredoc(root, shell, infile);
	ft_end_heredoc(infile, gnl);
	free(root->str);
	return (temp_n);
}

int	ft_open_heredoc(t_node *root, t_shell *shell)
{
	const int	std = dup(STDIN_FILENO);

	if (!root)
		return (1);
	if (root->left)
		ft_open_heredoc(root->left, shell);
	if (root->right && root->right->str && root->type & HEREDOC)
	{
		root->right->str = ft_heredoc(root->right, shell);
		root->type = REDIN;
		if (g_status == SIGINT)
		{
			dup2(std, STDIN_FILENO);
			g_status = 0;
			unlink(root->right->str);
			return (0);
		}
	}
	return (1);
}
