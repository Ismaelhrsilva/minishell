/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:12:49 by paranha           #+#    #+#             */
/*   Updated: 2024/06/29 20:11:29 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

char	**ft_env_export(const t_vector *vars)
{
	unsigned long	size;
	char			**env;
	unsigned long	i;
	t_vector		*line_dict;
	char			*full_string;

	if (!vars)
		return (NULL);
	size = ft_vector_size(vars);
	env = (char **)malloc((size + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (i < size)
	{
		line_dict = ft_vector_at(vars, i);
		full_string = ft_vector_at(line_dict, 3);
		if (full_string)
			env[i] = ft_strdup(full_string);
		else
			env[i] = NULL;
		i++;
	}
	env[size] = NULL;
	return (env);
}

void	ft_env_add(t_vector *vars, char *name, char *data)
{
	t_vector	*line_dict;
	char		*full_string;

	if (!vars || !name)
		return ;
	if (data)
		full_string = ft_strjoinsep(name, data, '=');
	else
		full_string = ft_strdup(name);
	line_dict = ft_build_line_envp(full_string);
	if (!line_dict)
	{
		free(full_string);
		return ;
	}
	ft_env_delete(vars, name);
	ft_vector_push_back(vars, line_dict);
	free(full_string);
}

void	ft_export_full_var(t_vector *env, char *arg, char *equal_sign)
{
	char	*name;
	char	*value;

	name = ft_substr(arg, 0, equal_sign - arg);
	if (ft_is_valid_name(name))
	{
		value = ft_strdup(equal_sign + 1);
		ft_env_add(env, name, value);
		free(name);
		free(value);
	}
	else
		free(name);
}

void	ft_export_arg(t_vector *env, char *arg)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
		ft_export_full_var(env, arg, equal_sign);
	else
	{
		if (ft_is_valid_name(arg) && !ft_getenv(env, arg))
			ft_env_add(env, arg, NULL);
	}
}

void	ft_builtin_export(t_shell *shell, t_vector *cmd)
{
	char	**vars;
	int		i;
	char	*arg;

	g_status = EXIT_SUCCESS;
	i = 1;
	while (i < cmd->size)
	{
		arg = ft_value(cmd, i, 0);
		ft_export_arg(shell->envp_dict, arg);
		i++;
	}
	if (i == 1)
	{
		vars = ft_env_export(shell->envp_dict);
		ft_sort_vars(vars, 0);
		i = 0;
		while (vars[i])
			ft_putendl_fd(vars[i++], STDOUT_FILENO);
		ft_freesplit(vars);
	}
}
