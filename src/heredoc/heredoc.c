/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:17:01 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/11 20:10:00 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

static long	ft_count()
{
	static long count;
	
	return(count++);
}

static void	ft_end_heredoc(void)
{
	if (g_status != SIGINT)
		ft_putstr_fd("bash: warning: here-document delimited by end-of-file\n", 2);
}

char    *ft_heredoc(char *delimiter)
{
 	char   	*gnl;
    int		size;
    int		size_gnl;
    int		infile;
	char	*temp_n;
	const int	std = dup(STDIN_FILENO);

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
			dup2(std ,STDIN_FILENO);
        if (gnl)
            size_gnl = ft_strlen(gnl);
        else
            break ;
        size = ft_strlen(delimiter);
        if (gnl && ft_strncmp(gnl, delimiter, size) == 0 && size == size_gnl)
            break ;
		gnl = ft_strjoin(gnl, "\n");
        ft_putstr_fd(gnl, infile);
        free(gnl);
    }
    free(gnl);
	close(infile);
    return (temp_n);
}

void	ft_open_heredoc(t_node *root)
{
	if (!root)
		return ;
	if (root->type & HEREDOC)
	{
		root->right->str = ft_heredoc(root->right->str);
		root->type = REDIN;
		ft_end_heredoc();
		if (g_status == SIGINT)
			return ;
	}
	ft_open_heredoc(root->left);
	ft_open_heredoc(root->right);
}
