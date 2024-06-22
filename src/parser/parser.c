/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/21 21:08:01 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_arranging_prompt(t_parse *parse)
{
	int		size;
	char	*prompt_arranged;

	if (parse->prompt)
		size = ft_strlen(parse->prompt);
	if (ft_valid_brackets_str(parse->prompt))
		return ((void )printf("Error_2 \n"));
	prompt_arranged = malloc((size * 2) * sizeof(char *) + 1);
	if (!prompt_arranged)
		return ;
	parse->idx = malloc(sizeof(t_index));
	if (!parse->idx)
	{
		free(prompt_arranged);
		return ;
	}
	parse->idx->i = 0;
	parse->idx->j = 0;
	while (parse->prompt[parse->idx->i] != '\0')
	{
		// if (ft_strchr("\'\"", parse->prompt[parse->idx->i]))
		ft_parse_quotes(parse, prompt_arranged);
		ft_parse_brackets(parse, prompt_arranged);
		if (!ft_parse_char(parse, prompt_arranged))
			prompt_arranged[parse->idx->j] = parse->prompt[parse->idx->i];
		parse->idx->i++;
		parse->idx->j++;
	}
	prompt_arranged[parse->idx->j] = '\0';
	parse->prompt_arranged = prompt_arranged;
}

char	**ft_parser(t_parse *parse)
{
	char	**split;
	int		i;
	int		m;

	i = 0;
	ft_arranging_prompt(parse);
	split = ft_split(parse->prompt_arranged, ' ');
	ft_change_sub_space(split);
	return (split);
}
