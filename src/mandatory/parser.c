/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/12 20:27:02 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/minishell.h"

void ft_parse_quotes(t_parse *parse, char *prompt)
{
	char	*signal;

	signal = "";
	if (ft_strchr("\'\"", parse->prompt[parse->idx->i]))
	{
		prompt[parse->idx->j++] = ' '; 
		if (ft_strchr("\"", parse->prompt[parse->idx->i]))
		{
			prompt[parse->idx->j++] = '\"';
			signal = "\"";
		}
		else
		{
			prompt[parse->idx->j++] = '\''; 
			signal = "\'";
		}
		parse->idx->i++;
		while (!ft_strchr(signal, parse->prompt[parse->idx->i]))
		{
			if (parse->prompt[parse->idx->i] == ' ')
			{
				prompt[parse->idx->j++] = 0x1A;
				parse->idx->i++;
			}
			else
				prompt[parse->idx->j++] = parse->prompt[parse->idx->i++];
		}
	}
}

int ft_aux_parse_char(char *ch, t_parse *parse, char *prompt)
{
	if (ft_strncmp(ch, &parse->prompt[parse->idx->i], 2) == 0)
	{
		prompt[parse->idx->j++] = ' '; 
		prompt[parse->idx->j++] = parse->prompt[parse->idx->i++];
		prompt[parse->idx->j++] = parse->prompt[parse->idx->i];
		prompt[parse->idx->j] = ' '; 
		return (1);
	}
	return (0);
}

int ft_parse_char(t_parse *parse, char *prompt)
{
	if (ft_aux_parse_char("<<", parse, prompt))
		return (1);
	else if (ft_aux_parse_char(">>", parse, prompt))
		return (1);
	else if (ft_aux_parse_char("&&", parse, prompt))
		return (1);
	else if (ft_aux_parse_char("||", parse, prompt))
		return (1);
	else if (ft_strchr("><|", parse->prompt[parse->idx->i]))
	{
		prompt[parse->idx->j++] = ' '; 
		prompt[parse->idx->j++] = parse->prompt[parse->idx->i];
		prompt[parse->idx->j] = ' '; 
		return (1);
	}
	return (0);
}

void	ft_arranging_prompt(t_parse *parse)
{
	int	size;
	char	*prompt_arranged;

	if (parse->prompt)
		size = ft_strlen(parse->prompt);
	prompt_arranged = malloc((size * 2) * sizeof(char *));
	if (!prompt_arranged)
		return ;
	parse->idx = malloc(sizeof(t_index));
	if (!parse->idx)
		return ;
	parse->idx->i = 0;
	parse->idx->j = 0;
	while (parse->prompt[parse->idx->i] != '\0')
	{
		if (ft_strchr("\'\"", parse->prompt[parse->idx->i]))
			ft_parse_quotes(parse, prompt_arranged);
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
	int		j;
	int		m;


	i = 0;
	m = 0;
	j = 0;
	ft_arranging_prompt(parse);
	split = ft_split(parse->prompt_arranged, ' ');
	while (split[m])
	{
		while (split[m][j])
		{
			if (split[m][j] == 0x1A)
				split[m][j] = ' ';
			j++;
		}
		m++;
	}
	while (split[i])
	{
		//ft_printf("%s\n", split[i]);
		ft_printf("Token--> %s\n", ft_set_token(split[i]));
		i++;
	}
	return split;
}
