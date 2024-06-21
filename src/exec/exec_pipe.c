/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:34:11 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/21 20:01:18 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

static void	ending_call_pipe(int side, pid_t pid, int status, int *fd)
{
	if (side == RIGHT)
	{
		close_fd(fd);
		waitpid(pid, &status, WUNTRACED);
		g_status = WEXITSTATUS(status);
	}
}

static void	dup_aux(int *fd, int side)
{
	if (side == LEFT)
		dup2(fd[1], STDOUT_FILENO);
	if (side == RIGHT)
		dup2(fd[0], STDIN_FILENO);
}

static void ft_execution_side(t_node *root, t_shell *shell, int side)
{
	if (side == LEFT)
		ft_execution(root->left, shell);
	if (side == RIGHT)
		ft_execution(root->right, shell);
}

static void	ft_pipe_aux(t_node *root, t_shell *shell, int *fd, int side)
{
	pid_t	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid < 0)
		exit (0);
	if (pid == 0)
	{
		status_here(FORK, 1);
		rl_clear_history();
		dup_aux(fd, side);
		close_fd(fd);
		ft_execution_side(root, shell, side);
		exit (0);
	}
	ending_call_pipe(side, pid, status, fd);
}

void	ft_pipe(t_node *root, t_shell *shell)
{
	int	fd[2];

	if (pipe(fd) < 0)
		exit (0);
	ft_pipe_aux(root, shell, fd, LEFT);
	ft_pipe_aux(root, shell, fd, RIGHT);
}
