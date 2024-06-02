/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/02 18:26:51 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int	i;
	int	j;
	char **ev;

	shell = malloc(sizeof(t_shell));
	if (shell == NULL)
		return (EXIT_FAILURE);
	shell->envp = envp;
	ft_envp(shell);
	i = 0;
	while (i < shell->envp_dict->size)
	{
		ft_printf("%s\n", ft_value(shell->envp_dict, i, 0));
		j = 0;
		ev = ft_value(shell->envp_dict, i, 1);
		ft_printf("-----------------------------------------\n");
		while (j < ft_count_matrix(ev))
			ft_printf("--valor --->%s\n", ev[j++]);
		i++;
	}
	ft_printf("-----------------------------------------\n");
	while (i < ft_count_matrix(shell->envp))
		printf("%s\n", envp[i++]);
	//read_line(shell);
	return (0);
}
