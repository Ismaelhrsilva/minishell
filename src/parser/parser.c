/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/30 17:09:50 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_parser(t_parse *parse)
{
	char	**split;
	int		i;
	int		m;

	i = 0;
	ft_arranging_prompt(parse);
	split = ft_split(parse->prompt_arranged, ' ');
	ft_change_sub_space(split);
	//parse->phrase = ft_construct_phrase(split, m);
	//ft_grammar_rules(parse->phrase);
	while (split[i])
	{
		ft_printf("%s\n", split[i]);
		//ft_printf("Token--> %d\n", ft_set_token(split[i]));
		//ft_printf("----------------------------------------------\n");
		i++;
	}
	return split;
}
