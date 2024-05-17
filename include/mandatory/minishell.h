/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:25:14 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/17 19:22:12 by ishenriq         ###   ########.fr       */
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

typedef enum e_token
{
	WORD = 0,
	REDIN = 1 << 0,
	REDOUT =  1 << 1,
	REDIRECTS = 3,
	HEREDOC = 1 << 2,
	APPEND =  1 << 3,
	REDALL = 15,
	OR = 1 << 4,
	AND = 1 << 5,
	PIPE = 1 << 6,
	ALLEXRED = 112,
	ALLEXHEREDOC = 121,
	ALL = 127,
	OPEN_BRACKET = 1 << 7,
	CLOSE_BRACKET = 1 << 8
} t_token;

typedef struct s_word
{
	char	*word;
	int		token;
}	t_word;

typedef struct s_phrase
{
	t_list	*words;
	int	size;
}	t_phrase;

typedef struct s_index
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
	t_phrase *phrase;
} t_parse;

typedef struct s_shell
{
	char	**prompt_splitted;
}	t_shell;

//File: Read_inputs
void	read_line(t_shell *shell);

//File Parse
char	**ft_parser(t_parse *parse);
void ft_parse_quotes(t_parse *parse, char *prompt);
int ft_aux_parse_char(char *ch, t_parse *parse, char *prompt);
int ft_parse_char(t_parse *parse, char *prompt);
void	ft_arranging_prompt(t_parse *parse);

//File Tokenazer
int	ft_set_token(char *str);

//File	Phrase 
t_phrase	*ft_construct_phrase(char **split, int m);

//File Grammar
void	ft_grammar_rules(t_phrase *phrase);

//File Utils
int	ft_power(int nb, int power);


//File grammar utils

int	ft_get_token(t_phrase *phrase, int pos);
int	ft_token_equal(t_phrase *phrase, int pos, int flag);
int	ft_count_token(t_phrase *phrase, int token);

#endif
