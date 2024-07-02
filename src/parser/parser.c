/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/01 17:55:12 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_arranging_prompt(t_parse *parse)
{
	int		size;
	char	*prompt_arranged;
	char	*signal;

	if (parse->prompt)
		size = ft_strlen(parse->prompt);
	prompt_arranged = malloc((size * 2) * sizeof(char *) + 1);
	parse->idx = malloc(sizeof(t_index));
	parse->idx->i = 0;
	parse->idx->j = 0;
	while (parse->prompt[parse->idx->i] != '\0')
	{
		if (ft_strchr("\'\"", parse->prompt[parse->idx->i]))
			ft_parse_quotes(parse, prompt_arranged, signal);
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
