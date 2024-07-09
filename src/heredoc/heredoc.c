/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:17:01 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/09 20:47:52 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

static long	ft_count(void)
{
	static long	count;

	return (count++);
}

static void	ft_end_heredoc(int infile, const int std, char *gnl)
{
	if (gnl)
		free (gnl);
	else if (g_status != SIGINT)
	{
		ft_putstr_fd("bash: warning: ", 2);
		ft_putstr_fd("here-document delimited by end-of-file\n", 2);
	}
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

char	*ft_heredoc(t_node *root, t_shell *shell)
{
	char		*gnl;
	int			infile;
	char		*temp_n;
	const int	std = dup(STDIN_FILENO);
	char		*limiter;
	char		*itoa_count;
	char		*gnl_temp;

	itoa_count = ft_itoa(ft_count());
	temp_n = ft_strjoin(TEMP, itoa_count);
	free(itoa_count);
	infile = open(temp_n, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		status_here(HERE_DOC, 1);
		gnl = readline("> ");
		status_here(HERE_DOC, 0);
		ft_heredoc_sigint(gnl, std);
		limiter = root->str;
		if (ft_count_chr(limiter, '\"') != 0
			|| ft_count_chr(limiter, '\'') != 0)
			limiter = ft_eliminate_signal(limiter, shell);
		if (gnl && ft_strncmp(gnl, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(limiter) == ft_strlen(gnl))
			break ;
		if (ft_count_chr(root->str_not_expanded, '\'') == 0
	  		&& ft_count_chr(root->str_not_expanded, '\"') == 0)
		{
			gnl_temp = gnl;
			gnl = ft_parse_expand_heredoc(gnl, shell);
			free(gnl_temp);
		}
		if (ft_strncmp(gnl, "0x1A", 4) != 0)
		{
			gnl_temp = gnl;
			gnl = ft_strjoin(gnl, "\n");
			free(gnl_temp);
			ft_putstr_fd(gnl, infile);
			free(gnl);
		}
	}
	ft_end_heredoc(infile, std, gnl);
	free(root->str);
	return (temp_n);
}

void	ft_open_heredoc(t_node *root, t_shell *shell)
{
	if (!root)
		return ;
	if (root->left)
		ft_open_heredoc(root->left, shell);
	if (root->right && root->right->str && root->type & HEREDOC)
	{
		root->right->str = ft_heredoc(root->right, shell);
		root->type = REDIN;
		if (g_status == SIGINT)
		{
			unlink(root->right->str);
			free(root->right->str);
			return ;
		}
	}
}
