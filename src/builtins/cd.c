/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:11:58 by paranha           #+#    #+#             */
/*   Updated: 2024/06/27 17:19:37 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_vector *env, char *new_pwd)
{
	char	*old_pwd;

	old_pwd = ft_getenv(env, "PWD");
	if (old_pwd)
		ft_env_add(env, "OLDPWD", old_pwd);
	ft_env_add(env, "PWD", new_pwd);
}

static int	change_directory(t_vector *env, char *path)
{
	char	new_pwd[PATH_MAX];

	if (chdir(path) != 0)
		return (-1);
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
		return (-1);
	update_pwd(env, new_pwd);
	return (0);
}

void	handle_cd_dash(t_shell *shell, char **dir)
{
	*dir = ft_getenv(shell->envp_dict, "OLDPWD");
	if (!*dir)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		ft_status(1);
	}
}

void	get_cd_directory(t_shell *shell, t_vector *cmd, char **dir)
{
	char	*arg;

	if (ft_value(cmd, 1, 0))
	{
		arg = ft_value(cmd, 1, 0);
		if (ft_strcmp(arg, "-") == 0)
			handle_cd_dash(shell, dir);
		else
			*dir = arg;
	}
	if (!*dir)
	{
		*dir = ft_getenv(shell->envp_dict, "HOME");
		if (!*dir)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			ft_status(1);
		}
	}
}

void	builtin_cd(t_shell *shell, t_vector *cmd)
{
	char	*dir;

	dir = NULL;
	if (cmd->size > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		ft_status(1);
		return ;
	}
	get_cd_directory(shell, cmd, &dir);
	if (!dir)
		return ;
	if (change_directory(shell->envp_dict, dir) != 0)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(dir);
		ft_status(1);
		return ;
	}
	g_status = EXIT_SUCCESS;
	ft_status(g_status);
}
