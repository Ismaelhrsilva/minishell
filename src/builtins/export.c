/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:12:49 by paranha           #+#    #+#             */
/*   Updated: 2024/06/24 19:03:23 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

void	ft_freesplit(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*strjoinsep(char *s1, char *s2, unsigned int sep)
{
	char	*new;
	size_t	size1;
	size_t	size2;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	new = (char *)malloc((size1 + size2 + 2) * sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcpy(new, s1, size1 + 1);
	new[size1] = sep;
	ft_strlcpy(new + size1 + 1, s2, size2 + 1);
	return (new);
}

void	ft_env_delete(t_vector *vars, char *name)
{
	unsigned long	i;
	t_vector		*line_dict;
	char			*identifier;

	if (!vars || !name)
		return ;
	i = 0;
	while (i < ft_vector_size(vars))
	{
		line_dict = ft_vector_at(vars, i);
		identifier = ft_vector_at(line_dict, 0);
		if (identifier && ft_strcmp(identifier, name) == 0)
		{
			ft_vector_erase(vars, i);
			return ;
		}
		i++;
	}
}

char	**env_export(const t_vector *vars)
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
		full_string = strjoinsep(name, data, '=');
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

void	sort_vars(char **argv, int minor)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (argv[i])
	{
		minor = i;
		j = i;
		while (argv[j])
		{
			if (ft_strncmp(argv[j], argv[minor], ft_strchr(argv[j], '=')
					- argv[j]) < 0)
				minor = j;
			j++;
		}
		if (i != minor)
		{
			tmp = argv[i];
			argv[i] = argv[minor];
			argv[minor] = tmp;
		}
		i++;
	}
}

void	export_arg(t_vector *env, char *arg)
{
	char	*equal_sign;
	char	*name;
	char	*value;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		name = ft_substr(arg, 0, equal_sign - arg);
		value = ft_strdup(equal_sign + 1);
		ft_env_add(env, name, value);
		free(name);
		free(value);
	}
	else
	{
		if (!ft_getenv(env, arg))
			ft_env_add(env, arg, NULL);
	}
}

void	builtin_export(t_shell *shell, t_vector *cmd)
{
	char		**vars;
	int			i;
	t_vector	*word;
	char		*arg;

	g_status = EXIT_SUCCESS;
	i = 1;
	while (i < cmd->size)
	{
		arg = ft_value(cmd, i, 0);
		printf("Processing argument: %s\n", arg);
		export_arg(shell->envp_dict, arg);
		i++;
	}
	if (i == 1)
	{
		printf("No arguments provided to export, displaying env variables\n");
		vars = env_export(shell->envp_dict);
		sort_vars(vars, 0);
		i = 0;
		while (vars[i])
		{
			ft_putendl_fd(vars[i], STDOUT_FILENO);
			i++;
		}
		ft_freesplit(vars);
	}
}
