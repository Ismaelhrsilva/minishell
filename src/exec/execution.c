/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:15:25 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/26 18:57:19 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_build_argv_exec(t_vector *phrase)
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
	char	*cmd;

	cmd = ft_get_pathname(shell->path_splitted, ft_value(phrase, 0, 0));
	if (cmd && (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0))
	{
		pid = fork();
		if (!pid)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			status_here(FORK, 1);
			rl_clear_history();
			if (access(cmd, F_OK) < 0)
				ft_error(cmd, NULL, "No such file or directory", ENOENT);
			else if (access(cmd, X_OK) < 0)
				ft_error(cmd, NULL, "Permission denied", EACCES);
			else if (execve(ft_get_pathname(shell->path_splitted, cmd),
					ft_build_argv_exec(phrase), shell->envp) < 0)
				ft_error(cmd, NULL, strerror(errno), errno);
			close(g_status);
		}
		ft_pid_status(pid);
	}
	else
		ft_error(cmd, NULL, "command not found", ENOENT);
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

int	ft_builtins(t_node *root, t_shell *shell)
{
	if (root->str && ft_strcmp(root->str, "export") == 0)
		builtin_export(shell, root->phrase);
	else if (root->str && ft_strcmp(root->str, "env") == 0)
		ft_env_builtin(shell, root->phrase);
	else if (root->str && ft_strcmp(root->str, "pwd") == 0)
		builtin_pwd(shell, root->phrase);
	else if (root->str && ft_strcmp(root->str, "unset") == 0)
		builtin_unset(shell, root->phrase);
	else if (root->str && ft_strcmp(root->str, "exit") == 0)
		builtin_exit(shell, root->phrase);
	else if (root->str && ft_strcmp(root->str, "echo") == 0)
		builtin_echo(shell, root->phrase);
	else if (root->str && ft_strcmp(root->str, "cd") == 0)
		builtin_cd(shell, root->phrase);
	else
		return (0);
	return (1);
}

void	ft_expand_before_exec(t_node *root, t_shell *shell)
{
	int		i;
	char	*str;

	i = 0;
	while (i < root->phrase->size)
	{
		str = ft_value(root->phrase, i, 0);
		((t_vector *)root->phrase->values[i])->values[0] = ft_parse_expand(str,
				shell);
		i++;
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
		ft_expand_before_exec(root, shell);
		if (ft_builtins(root, shell))
			return ;
		if (root->str && root->str[0] == '(')
		{
			ft_eliminate_ch_corner(root->str);
			ft_exec_brackets(root, shell);
		}
		else if (root->str && root->fd != -1)
			ft_do(root->phrase, shell);
	}
}
