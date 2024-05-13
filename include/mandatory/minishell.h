/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:25:14 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/13 19:44:20 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>     // malloc, free
# include <unistd.h>     // access, close, fork, execve, dup, dup2, pipe, getcwd, chdir
# include <fcntl.h>      // open
# include <sys/types.h>  // wait, waitpid, wait3, wait4, signal, stat, lstat, fstat, unlink
# include <signal.h>     // sigaction, sigemptyset, sigaddset, kill
# include <dirent.h>     // opendir, readdir, closedir
# include <string.h>     // strerror
# include <errno.h>      // perror
# include <termios.h>    // isatty, ttyname, tcsetattr, tcgetattr
# include <sys/ioctl.h>  // ioctl
# include <curses.h>     // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../lib/libft/libft.h"
# include "../lib/printf/ft_printf.h"
# include "../lib/libft/gnl/get_next_line.h"

/*enum e_token
{
	WORD = 0,
	REDIN = 1,
	REDOUT =  2,
	HEREDOC = 3,
	APPEND =  4,
	OR = 5,
	AND = 6,
	PIPE = 7
}	t_token;*/

typedef	struct s_index
{
	int	i;
	int	j;
	int	m;
}	t_index;

typedef struct s_parse
{
	char	*prompt;
	char	*prompt_arranged;
	t_index	*idx;
} t_parse;

typedef struct s_shell
{
	char	**prompt_splitted;
}	t_shell;

//File: Read_inputs
void	read_line(t_shell *shell);

//File parse
char	**ft_parser(t_parse *parse);
void ft_parse_quotes(t_parse *parse, char *prompt);
int ft_aux_parse_char(char *ch, t_parse *parse, char *prompt);
int ft_parse_char(t_parse *parse, char *prompt);
void	ft_arranging_prompt(t_parse *parse);


//File Tokenazer
int	ft_set_token(char *str);

#endif
