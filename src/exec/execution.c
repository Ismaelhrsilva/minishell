/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:15:25 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/08 18:52:19 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

static void	ft_pid_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (status == 139)
		status = 1;
	g_status = status;
}

static	char **ft_build_argv_exec(t_vector *phrase)
{
	char	**argv_exec;
	int		i;

	i = 0;
	argv_exec = ft_calloc(phrase->size + 1, sizeof(char **));
	while (i < phrase->size)
	{
		argv_exec[i] = ft_value(phrase, i, 0);
		i++;
	}
	argv_exec[i] = NULL;
	return (argv_exec);
}

static void	ft_do(t_vector *phrase, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		/*int i;
		char ** matrix;
		i = 0;
		matrix = ft_build_argv_exec(phrase);
		while (matrix[i])
		{
			ft_putstr_fd(matrix[i], 2);
			ft_putstr_fd("\n", 2);
			i++;
		}*/
		if (execve(ft_get_pathname(shell->path_splitted, ft_value(phrase, 0, 0)),
		ft_build_argv_exec(phrase), shell->envp) < 0)
			g_status = errno;
			//exit(ft_status(-1));
	}
	ft_pid_status(pid);
}


static void	ft_or_and(t_node *root, t_shell *shell)
{
	if (root->type & OR)
	{
		ft_execution(root->left, shell);
		if (g_status > 0)
			ft_execution(root->right, shell);
	}
	else
	{
		ft_execution(root->left, shell);
		if (g_status == 0)
			ft_execution(root->right, shell);
	}
}

void	ft_execution(t_node *root, t_shell *shell)
{
	if (!root)
		return ;
	if (root->type & OR_AND)
		ft_or_and(root, shell);
	else if (root->type & PIPE)
		ft_pipe(root, shell);
	else if (root->type & REDALL)
		ft_exec_redirects(root, shell);
	else if (root->left)
		ft_execution(root->left, shell);
	else if (root->right)
		ft_execution(root->right, shell);
	else if (root->type == EXEC && root->phrase)
	{
		ft_do(root->phrase, shell);
	}
}
