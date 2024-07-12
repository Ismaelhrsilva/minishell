/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/12 15:14:14 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

int	ft_prompt_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_is_space(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_to_execute_aux(t_shell *shell)
{
	if (!ft_open_heredoc(shell->root, shell))
	{
		ft_clear_ast(shell->root);
		ft_freephrase(shell->parse->phrase_grammar);
		ft_freephrase(shell->parse->phrase);
		return ;
	}
	if (ft_grammar_rules(shell->parse->phrase_grammar))
	{
		ft_freephrase(shell->parse->phrase_grammar);
		ft_execution(shell->root, shell);
	}
	else
		if (shell->parse->phrase_grammar)
			ft_freephrase(shell->parse->phrase_grammar);
	ft_clear_ast(shell->root);
}

void	ft_to_execute(char *str, t_shell *shell)
{
	if (!str || ft_strlen(str) == 0 || ft_prompt_only_space(str))
		return ;
	shell->parse = malloc(sizeof(t_parse));
	shell->parse->prompt = str;
	shell->parse->prompt_splitted = ft_parser(shell->parse);
	shell->parse->phrase = \
		ft_construct_phrase(shell->parse->prompt_splitted, shell);
	shell->parse->phrase_grammar = \
		ft_construct_phrase(shell->parse->prompt_splitted, shell);
	ft_order_redall(shell->parse->phrase);
	shell->root = ft_ast(shell->parse->phrase);
	if (shell->root)
		ft_to_execute_aux(shell);
	ft_free_matrix(shell->parse->prompt_splitted);
	free(shell->parse);
	return ;
}

char	*read_line(t_shell *shell)
{
	char	*prompt;

	status_here(PROMPT, 0);
	prompt = readline("minishell>$ ");
	status_here(PROMPT, 1);
	if (!prompt)
	{
		printf("exit\n");
		ft_free_shell(shell);
		exit(0);
	}
	add_history(prompt);
	return (prompt);
}
