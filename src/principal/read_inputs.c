/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/20 19:13:32 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

void	ft_to_execute(char *str, t_shell *shell)
{
	t_parse	*parse;
	char	**prompt_splitted;
	t_node	*root;

	parse = malloc(sizeof(t_parse));
	if (!parse)
		return ;
	parse->prompt = str;
	prompt_splitted = ft_parser(parse);
	parse->phrase = ft_construct_phrase(prompt_splitted, shell);
	ft_grammar_rules(parse->phrase);
	//if (g_status == 2)
	//if (ft_status(-1))
	//	return ;
	ft_order_redall(parse->phrase);
	//ft_print_vector_content(parse->phrase);
	root = ft_ast(parse->phrase);
	ft_open_heredoc(root, shell);
	ft_execution(root, shell);
	//ft_print_ast(root, "root");
	free(root);
	parse->phrase = NULL;
	root = NULL;
	return ;
}

char	*read_line(void)
{
	char *prompt;

	status_here(PROMPT, 0);
	prompt = readline("minishell>$ ");
	status_here(PROMPT, 1);
	if (!prompt)
		exit (255);
	add_history(prompt);
	//if (ft_strncmp(prompt, "exit", 4) ==  0)
	//	return (NULL);
	return (prompt);
}
