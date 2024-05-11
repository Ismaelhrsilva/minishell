/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/10 22:02:13 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/minishell.h"

static void ft_parse_quotes(s_minishell *minishell, int *i, int *j, char *prompt)
{
	char	*signal;

	signal = "";
	if (ft_strchr("\'\"", minishell->prompt[*i]))
	{
		prompt[(*j)++] = ' '; 
		if (ft_strchr("\"", minishell->prompt[*i]))
		{
			prompt[(*j)++] = '\"';
			signal = "\"";
		}
		else
		{
			prompt[(*j)++] = '\''; 
			signal = "\'";
		}
		(* i)++;
		while (!ft_strchr(signal, minishell->prompt[*i]))
		{
			if (minishell->prompt[*i] == ' ')
			{
				prompt[(*j)++] = 0x1A;
				(* i)++;
			}
			else
				prompt[(*j)++] = minishell->prompt[(*i)++];
		}
	}
}

static int ft_parse_char(s_minishell *minishell, int *i, int *j, char *prompt)
{
	if (ft_strncmp("<<", &minishell->prompt[*i], 2) == 0)
	{
		prompt[(*j)++] = ' '; 
		prompt[(*j)++] = minishell->prompt[(*i)++];
		prompt[(*j)++] = minishell->prompt[(*i)];
		prompt[(*j)] = ' '; 
		return (1);
	}
	else if (ft_strncmp("&&", &minishell->prompt[*i], 2) == 0)
	{
		prompt[(*j)++] = ' '; 
		prompt[(*j)++] = minishell->prompt[(*i)++];
		prompt[(*j)++] = minishell->prompt[(*i)];
		prompt[(*j)] = ' '; 
		return (1);
	}
	else if (ft_strncmp("||", &minishell->prompt[*i], 2) == 0)
	{
		prompt[(*j)++] = ' '; 
		prompt[(*j)++] = minishell->prompt[(*i)++];
		prompt[(*j)++] = minishell->prompt[(*i)];
		prompt[(*j)] = ' '; 
		return (1);
	}
	else if (ft_strchr("><|", minishell->prompt[*i]))
	{
		prompt[(*j)++] = ' '; 
		prompt[(*j)++] = minishell->prompt[*i];
		prompt[(*j)] = ' '; 
		return (1);
	}
	return (0);
}

static void	ft_arranging_prompt(s_minishell *minishell)
{
	int	size;
	char	*prompt_arranged;
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (minishell->prompt)
		size = ft_strlen(minishell->prompt);
	prompt_arranged = malloc((size * 2) * sizeof(char *));
	if (!prompt_arranged)
		return ;
	while (minishell->prompt[i] != '\0')
	{
		if (ft_strchr("\'\"", minishell->prompt[i]))
			ft_parse_quotes(minishell, &i, &j, prompt_arranged);
		if (!ft_parse_char(minishell, &i, &j, prompt_arranged))
			prompt_arranged[j] = minishell->prompt[i];
		i++;
		j++;
	}
	prompt_arranged[j] = '\0';
	minishell->prompt_arranged = prompt_arranged;
}

void	ft_parser(s_minishell *minishell)
{
	char	**split;
	int		i;
	int		j;
	int		m;


	i = 0;
	m = 0;
	j = 0;
	ft_arranging_prompt(minishell);
	split = ft_split(minishell->prompt_arranged, ' ');
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
		ft_printf("%s\n", split[i++]);
}
