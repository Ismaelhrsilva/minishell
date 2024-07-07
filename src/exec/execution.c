/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:15:25 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/07 19:43:40 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

static char	**ft_build_argv_exec(t_vector *phrase)
{
	char	**argv_exec;
	size_t	i;

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
	char	**vars;
	char	**argv_exec;

	vars = ft_env_export(shell->envp_dict);
	shell->path = ft_getenv(shell->envp_dict, "PATH");
	shell->path_splitted = ft_split(shell->path, ':');
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
			argv_exec = ft_build_argv_exec(phrase);
			if (access(cmd, F_OK) < 0)
				ft_error(cmd, NULL, "No such file or directory", ENOENT);
			else if (access(cmd, X_OK) < 0)
				ft_error(cmd, NULL, "Permission denied", EACCES);
			else if (execve(ft_get_pathname(shell->path_splitted, cmd),
					argv_exec, vars) < 0)
				ft_error(cmd, NULL, strerror(errno), errno);
			close(g_status);
			ft_free_matrix(argv_exec);
			ft_free_matrix(vars);
			free(cmd);
			ft_clear(shell);
			exit(ft_status(-1));
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
		if (ft_status(-1) > 0)
			ft_execution(root->right, shell);
	}
	else
	{
		ft_execution(root->left, shell);
		if (ft_status(-1) == 0)
			ft_execution(root->right, shell);
	}
}

int	ft_builtins(t_node *root, t_shell *shell)
{
	if (root->str && ft_strcmp(root->str, "export") == 0)
		ft_builtin_export(shell, root->phrase);
	else if (root->str && ft_strcmp(root->str, "env") == 0)
		ft_builtin_env(shell, root->phrase);
	else if (root->str && ft_strcmp(root->str, "pwd") == 0)
		ft_builtin_pwd(shell, root->phrase);
	else if (root->str && ft_strcmp(root->str, "unset") == 0)
		ft_builtin_unset(shell, root->phrase);
	else if (root->str && ft_strcmp(root->str, "exit") == 0)
		ft_builtin_exit(shell, root->phrase);
	else if (root->str && ft_strcmp(root->str, "echo") == 0)
		ft_builtin_echo(shell, root->phrase);
	else if (root->str && ft_strcmp(root->str, "cd") == 0)
		ft_builtin_cd(shell, root->phrase);
	else
		return (0);
	return (1);
}

t_vector	*ft_put_str_token_at_vector(t_vector *phrase, int i, char *str)
{
	t_vector	*innervector;

	innervector = ft_vector_create();
	ft_vector_push_back(innervector, ft_strdup(str));
	ft_vector_push_back(innervector, ft_value(phrase, i, 1));
	return (innervector);
}

void	ft_expand_before_exec(t_node *root, t_shell *shell)
{
	size_t		i;
	char		*str;
	char		*str_temp;
	t_vector	*vector;

	i = 0;
	vector = ft_vector_create();
	while (i < root->phrase->size)
	{
		str_temp = ft_parse_expand(ft_value(root->phrase, i, 0), shell);
		str = ft_strdup(str_temp);
		if (ft_strncmp(str, "0x1A", 4) != 0)
		{
			ft_vector_push_back(vector, 
					ft_put_str_token_at_vector(root->phrase, i, str));
		}
		free(str_temp);
		free(str);
		i++;
	}
	if (root->phrase != NULL)
		ft_freephrase_2(root->phrase);
	root->phrase = vector;
}

// void	ft_expand_before_exec(t_node *root, t_shell *shell)
//{
//    size_t			i;
//    char			*str;
//    t_vector		*vector;
//
//    i = 0;
//    vector = ft_vector_create();
//    while (i < root->phrase->size)
//    {
//        str = ft_parse_expand(ft_value(root->phrase, i, 0), shell);
//        if (ft_strncmp(str, "0x1A", 4) != 0)
//        {
//            t_vector *inner_vector = ft_put_str_token_at_vector(root->phrase,
//		i, str);
//            ft_vector_push_back(vector, inner_vector);
//            ft_vector_free(inner_vector);
//        }
//        i++;
//    }
//    root->phrase = vector;
//}

/*void	ft_expand_before_exec(t_node *root, t_shell *shell)
{
	int			i;
	char		*str;
	t_vector	*vector;

	i = 0;
	vector = ft_vector_create();
	while (i < root->phrase->size)
	{
		str = ft_value(root->phrase, i, 0);
		printf("antes %s\n", str);
		((t_vector *)root->phrase->values[i])->values[0] = ft_parse_expand(str,
				shell);
		printf("depois %s\n", (char *)ft_value(root->phrase, i, 0));
		i++;
	}
}*/

//void	ft_free_root(t_node *root)
//{
//	if (root->left)
//		ft_free_root(root->left);
//	if (root->right)
//		ft_free_root(root->right);
//	if (root->phrase)
//		ft_vector_free(root->phrase);
//	free(root);
//}

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
	//else if (root->type == EXEC && root->phrase)
	else if (root->type == 0 && root->phrase)
	{
		ft_expand_before_exec(root, shell);
		if (root->phrase->size == 0)
			return ;
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
	// ft_free_phrase(root->phrase);
	// ft_vector_free(root->phrase);
}
