/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:10:42 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/09 20:01:21 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

extern volatile sig_atomic_t	g_status;

void	ft_error(char *cmd, char *flag, char *msg, int status)
{
	struct stat	path_stat;

	path_stat = (struct stat){0};
	stat((const char *) cmd, &path_stat);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (flag)
	{
		ft_putstr_fd(flag, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if ((ft_strchr("./", cmd[0]) || cmd[ft_strlen(cmd) - 1] == '/')
		&& status != ENOENT && path_stat.st_mode & S_IFDIR)
		ft_putstr_fd("Is a directory\n", STDERR_FILENO);
	else
		ft_putendl_fd(msg, STDERR_FILENO);
	if (status == EACCES)
		g_status = 126;
	else if (status == ENOENT)
		g_status = 127;
	else
		g_status = status;
	ft_status(g_status);
}

void	close_open_fds(void)
{
	struct dirent	*file;
	DIR				*root;
	int				fd;

	root = opendir("/proc/self/fd/");
	while (1)
	{
		file = readdir(root);
		if (!file)
			break ;
		fd = ft_atoi(file->d_name);
		if (fd > -1 && fd < 1024)
			close(ft_atoi(file->d_name));
	}
	closedir(root);
}

void	ft_clear(t_shell *shell)
{
	close_open_fds();
	if (shell->parse->phrase_grammar)
		ft_freephrase(shell->parse->phrase_grammar);
	if (shell->parse->phrase)
		ft_freephrase(shell->parse->phrase);
	shell->parse->phrase_grammar = NULL;
	shell->parse->phrase = NULL;
	ft_free_matrix(shell->parse->prompt_splitted);
	ft_clear_ast(shell->root);
	free(shell->root);
	free(shell->parse);
	ft_free_shell(shell);
}

void	ft_clear_pipe(t_shell *shell)
{
	if (shell->str)
		free(shell->str);
	ft_free_matrix(shell->parse->prompt_splitted);
	free(shell->parse);
	ft_clear_ast(shell->root);
	ft_clear_brackets(shell);
}
