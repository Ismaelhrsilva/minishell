/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_brackets.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:28:52 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/18 18:39:30 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_duplicate_matrix(char **matrix)
{
	int		i;
	char	**new_matrix;

	i = 0;
	if (!matrix)
		return (NULL);
	new_matrix = malloc((ft_count_matrix(matrix) + 1) * sizeof(char *));
	while (matrix[i] != NULL)
	{
		new_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	new_matrix[i] = NULL;
	return (new_matrix);
}

void	ft_clear_brackets(t_shell *shell)
{
	ft_free_envp_dict(shell->envp_dict);
	ft_freesplit(shell->path_splitted);
	free(shell);
}

void	ft_clear_brackets_before_exec(t_shell *shell)
{
	shell->parse->phrase_grammar = NULL;
	shell->parse->phrase = NULL;
	ft_free_matrix(shell->parse->prompt_splitted);
	ft_clear_ast(shell->root);
	free(shell->parse);
	ft_free_shell(shell);
}

void	ft_exec_brackets(t_node *root, t_shell *shell)
{
	pid_t		pid;
	t_shell		*shell_b;

	if (!shell->envp || shell->envp == NULL)
		return ;
	shell_b = malloc(sizeof(t_shell));
	shell_b->envp = ft_duplicate_matrix(shell->envp);
	pid = fork();
	if (pid == 0)
	{
		ft_status_here(FORK, 1);
		shell_b->str = ft_strdup(root->str);
		ft_envp(shell_b);
		ft_free_matrix(shell_b->envp);
		ft_clear_brackets_before_exec(shell);
		ft_to_execute(shell_b->str, shell_b);
		free(shell_b->str);
		ft_clear_brackets(shell_b);
		exit(ft_status(-1));
	}
	ft_free_matrix(shell_b->envp);
	free(shell_b);
	ft_pid_status(pid);
}
