/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:13:00 by paranha           #+#    #+#             */
/*   Updated: 2024/06/25 18:43:55 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

void	builtin_unset(t_shell *shell, t_vector *cmd)
{
	int			i;
	t_vector	*word;
	char		*arg;

	g_status = EXIT_SUCCESS;
	i = 0;
	while (cmd->values[++i])
	{
		word = (t_vector *)cmd->values[i];
		arg = (char *)word->values[0];
		//printf("Unsetting variable: %s\n", arg);
		ft_env_delete(shell->envp_dict, arg);
	}
}
