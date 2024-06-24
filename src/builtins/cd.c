/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:11:58 by paranha           #+#    #+#             */
/*   Updated: 2024/06/23 20:53:16 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_getenv(t_vector *env, const char *name)
{
	unsigned long	i;
	t_vector		*line;
	const char		*identifier;
	const char		*value;

	i = 0;
	if (!env || !name)
		return (NULL);
	while (i < ft_vector_size(env))
	{
		line = ft_vector_at(env, i);
		if (!line || ft_vector_size(line) < 2)
		{
			i++;
			continue ;
		}
		identifier = ft_vector_at(line, 0);
		value = ft_vector_at(line, 1);
		if (identifier && ft_strcmp(identifier, name) == 0)
			return ((char *)value);
		i++;
	}
	return (NULL);
}

static void	update_pwd(t_vector *env, const char *new_pwd)
{
	char	*old_pwd;

	old_pwd = ft_getenv(env, "PWD");
	if (old_pwd)
		ft_env_add(env, "OLDPWD", old_pwd);
	ft_env_add(env, "PWD", new_pwd);
}

static int	change_directory(t_vector *env, const char *path)
{
	char	new_pwd[PATH_MAX];

	if (chdir(path) != 0)
		return (-1);
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
		return (-1);
	update_pwd(env, new_pwd);
	return (0);
}

void	builtin_cd(t_shell *shell, t_vector *cmd)
{
	const char	*dir = NULL;
	int			lflag;
	int			i;
	t_vector	*word;
	char		*arg;

	lflag = 0;
	i = 1;
	if (cmd->size > 2)
	{
		fprintf(stderr, "cd: too many arguments\n");
		g_status = EXIT_FAILURE;
		return ;
	}
	if (cmd->values[i])
	{
		word = (t_vector *)cmd->values[i];
		arg = (char *)word->values[0];
		printf("Processing argument: %s\n", arg);
		if (ft_strcmp(arg, "-") == 0)
		{
			dir = ft_getenv(shell->envp_dict, "OLDPWD");
			if (!dir)
			{
				fprintf(stderr, "cd: OLDPWD not set\n");
				g_status = EXIT_FAILURE;
				return ;
			}
			lflag = 1;
		}
		else
			dir = arg;
	}
	if (!dir)
	{
		dir = ft_getenv(shell->envp_dict, "HOME");
		if (!dir)
		{
			fprintf(stderr, "cd: HOME not set\n");
			g_status = EXIT_FAILURE;
			return ;
		}
	}
	printf("Attempting to change directory to: %s\n", dir);
	if (change_directory(shell->envp_dict, dir) != 0)
	{
		perror("cd");
		g_status = EXIT_FAILURE;
		return ;
	}
	if (lflag)
		printf("%s\n", ft_getenv(shell->envp_dict, "PWD"));
	g_status = EXIT_SUCCESS;
}