/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/10 20:32:51 by ishenriq         ###   ########.fr       */
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

void	ft_to_execute(char *str, t_shell *shell)
{
	t_parse	*parse;
	t_node	*root;

	if (!str || ft_strlen(str) == 0 || ft_prompt_only_space(str))
		return ;
	parse = malloc(sizeof(t_parse));
	shell->parse = parse;
	parse->prompt = str;
	parse->prompt_splitted = ft_parser(parse);
	parse->phrase = ft_construct_phrase(parse->prompt_splitted, shell);
	parse->phrase_grammar = ft_construct_phrase(parse->prompt_splitted, shell);
	ft_order_redall(parse->phrase);
	shell->root = ft_ast(parse->phrase);
	if (shell->root)
	{
		ft_open_heredoc(root, shell);
		if (ft_grammar_rules(parse->phrase_grammar))
		{
			ft_freephrase(parse->phrase_grammar);
			ft_execution(root, shell);
		}
		else
		{
			if (shell->parse->phrase_grammar)
				ft_freephrase(shell->parse->phrase_grammar);
			shell->parse->phrase_grammar = NULL;
			shell->parse->phrase = NULL;
		}
		ft_clear_ast(root);
		root = NULL;
	}
	ft_free_matrix(shell->parse->prompt_splitted);
	free(parse);
	return ;
}

char	*read_line(void)
{
	char	*prompt;

	status_here(PROMPT, 0);
	prompt = readline("minishell>$ ");
	status_here(PROMPT, 1);
	if (!prompt)
		exit(0);
	add_history(prompt);
	return (prompt);
}
