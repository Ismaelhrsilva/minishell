/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:03:35 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/18 20:03:39 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_build_argv_exec(t_vector *phrase)
{
	char	**argv_exec;
	size_t	i;

	i = 0;
	argv_exec = ft_calloc(phrase->size + 1, sizeof(char **));
	while (i < phrase->size)
	{
		argv_exec[i] = ft_strdup(ft_value(phrase, i, 0));
		i++;
	}
	argv_exec[i] = NULL;
	return (argv_exec);
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
		if (ft_strncmp(str, "0x1A", 4) == 0)
			free(((t_vector *)root->phrase->values[i])->values[1]);
		free(str_temp);
		free(str);
		i++;
	}
	if (root->phrase != NULL)
		ft_freephrase_2(root->phrase);
	root->phrase = vector;
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
