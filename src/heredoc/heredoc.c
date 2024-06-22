/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:17:01 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/21 21:14:15 by ishenriq         ###   ########.fr       */
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
		ft_putstr_fd("bash: warning: here-document delimited by end-of-file\n", 2);
	close(infile);
	close(std);
}

char	*ft_heredoc(t_node *root, t_shell *shell)
{
	char		*gnl;
	int			size;
	int			size_gnl;
	int			infile;
	char		*temp_n;
	char		*delimiter;
	const int	std = dup(STDIN_FILENO);

	delimiter = root->str;
	temp_n = ft_strjoin(TEMP, ft_itoa(ft_count()));
	infile = open(temp_n, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (infile < 0)
	{
		printf("Errror in infile");
		return (NULL);
	}
	while (1)
	{
		status_here(HERE_DOC, 1);
		gnl = readline("> ");
		status_here(HERE_DOC, 0);
		if (g_status == SIGINT)
		{
			dup2(std, STDIN_FILENO);
			if (gnl)
			{
				free(gnl);
				gnl = NULL;
			}
		}
		if (gnl)
			size_gnl = ft_strlen(gnl);
		else
			break ;
		size = ft_strlen(delimiter);
		if (gnl && ft_strncmp(gnl, delimiter, size) == 0 && size == size_gnl)
			break ;
		if (!ft_strchr("\'\"", root->str_not_expanded[0]))
			gnl = ft_parse_expand_heredoc(gnl, shell);
		gnl = ft_strjoin(gnl, "\n");
		ft_putstr_fd(gnl, infile);
		free(gnl);
	}
	ft_end_heredoc(infile, std, gnl);
	return (temp_n);
}

void	ft_open_heredoc(t_node *root, t_shell *shell)
{
	if (!root)
		return ;
	if (root->type & HEREDOC)
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
	ft_open_heredoc(root->left, shell);
	ft_open_heredoc(root->right, shell);
}
