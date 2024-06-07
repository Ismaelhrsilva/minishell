/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:44:17 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/07 18:04:19 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

static void ft_close_fd_tmp(const int *fd)
{
	dup2(fd[0], STDOUT_FILENO);
	dup2(fd[1], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

static void	ft_change_fds(int fd, int new)
{
	if (fd != -1)
	{
		dup2(fd, new);
		close(fd);
	}
}

static void	ft_which_red(t_node *root, int flag)
{
	if (flag & REDOUT)
		root->fd = open(root->right->str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (flag & APPEND)
		root->fd = open(root->right->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
	 else if (flag & REDIN)
		root->fd = open(root->right->str, O_RDONLY, 0644);
}

static void	ft_redirects(t_node *root, t_shell *shell)
{
	int	flag;

	if (root->left->type & REDALL)
		ft_redirects(root->left, shell);
	flag |= root->type;
	if (root->type & (REDOUT | APPEND) &&
		(root->left->fd != -1 || g_status == 0))
	{
		ft_which_red(root, flag);
		ft_which_red(root, flag);
		ft_change_fds(root->fd, STDOUT_FILENO);
	}
	else if (root->type & (REDIN | HEREDOC) &&
		(root->left->fd != -1 || g_status == 0))
	{
		ft_which_red(root, flag);
		ft_change_fds(root->fd, STDOUT_FILENO);
	}
	else if (root->left->fd == -1)
		root->fd = -1;
}

void	ft_exec_redirects(t_node *root, t_shell *shell)
{
	const int	fd[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};

	if (!root->fd)
		ft_redirects(root, shell);
	if (g_status > 0 || root->fd == -1)
		return (ft_close_fd_tmp(fd));
	ft_execution(root->left, shell);
	ft_close_fd_tmp(fd);
}
