/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:25:14 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/01 21:23:02 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/gnl/get_next_line.h"
# include "../lib/libft/libft.h"
# include "../lib/printf/ft_printf.h"
# include <curses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <dirent.h> // opendir, readdir, closedir
# include <errno.h>  // perror
# include <fcntl.h>  // open
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h> // sigaction, sigemptyset, sigaddset, kill
# include <stdio.h>
# include <stdlib.h>    // malloc, free
# include <string.h>    // strerror
# include <sys/ioctl.h> // ioctl
# include <sys/types.h> // wait, waitpid, wait3, wait4, signal, stat, lstat, fstat, unlink
# include <termios.h>   // isatty, ttyname, tcsetattr, tcgetattr
# include <unistd.h>    // access, close, fork, execve, dup, dup2, pipe, getcwd, chdir

# define FT_VECTOR_INITIAL_CAPACITY 16

typedef enum e_token
{
	WORD = 0,
	REDIN = 1 << 0,
	REDOUT = 1 << 1,
	REDIRECTS = 3,
	HEREDOC = 1 << 2,
	APPEND = 1 << 3,
	REDALL = 15,
	OR = 1 << 4,
	AND = 1 << 5,
	OR_AND = 48,
	PIPE = 1 << 6,
	ALLEXRED = 112,
	ALLEXHEREDOC = 121,
	ALL = 127,
	OPEN_BRACKET = 1 << 7,
	CLOSE_BRACKET = 1 << 8,
	EXEC	= 1 << 9
}					t_token;

typedef struct s_vector
{
	void			**values;
	unsigned long	size;
	unsigned long	capacity;
}					t_vector;

typedef enum e_side
{
	LEFT = 0,
	RIGHT = 1
}					t_size;

typedef struct s_index
{
	int				i;
	int				j;
	int				m;
}					t_index;

typedef struct s_parse
{
	char			*prompt;
	char			*prompt_arranged;
	t_index			*idx;
	t_vector		*phrase;
}					t_parse;

typedef struct s_node
{
	char			*str;
	int				type;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct s_shell
{
	char			**prompt_splitted;
	t_node			*root;
}					t_shell;

// File: Read_inputs
void				read_line(t_shell *shell);

// File Parse
char				**ft_parser(t_parse *parse);

// File Parse Utils
void				ft_parse_quotes(t_parse *parse, char *prompt);
int					ft_aux_parse_char(char *ch, t_parse *parse, char *prompt);
int					ft_parse_char(t_parse *parse, char *prompt);
void				ft_arranging_prompt(t_parse *parse);

// File Tokenazer
int					ft_set_token(char *str);

// File	Phrase
t_vector			*ft_construct_phrase(char **split);
void				ft_free_phrase(t_vector *phrase);

// File Grammar
void				ft_grammar_rules(t_vector *phrase);

// File Utils
int					ft_power(int nb, int power);
int					ft_count_matrix(char **str);
void				ft_change_sub_space(char **split);

// File grammar utils
int					ft_count_token(t_vector *phrase, int token);
int					ft_pos_token(t_vector *phrase, int start, int end,
						int token);
int					ft_pos_token_back(t_vector *phrase, int token);
//File AST
t_node 	*ft_ast(t_vector *phrase);

// File Vector
bool				ft_vector_resize(t_vector *vector,
						unsigned long new_capacity);
t_vector			*ft_vector_create(void);
void				ft_vector_free(t_vector *vector);
void				ft_vector_push_back(t_vector *vector, void *value);
void				ft_vector_push_front(t_vector *vector, void *value);
void				ft_vector_pop_back(t_vector *vector);
void				ft_vector_pop_front(t_vector *vector);
unsigned long		ft_vector_insert(t_vector *vector, unsigned long position,
						void *value);
void				ft_vector_erase(t_vector *vector, unsigned long position);
void				*ft_vector_at(const t_vector *vector, unsigned long index);
void				*ft_value(const t_vector *vector, unsigned long i, unsigned long j);
int					ft_value_int(const t_vector *vector, unsigned long i, unsigned long j);
bool				ft_vector_empty(const t_vector *vector);
unsigned long		ft_vector_size(const t_vector *vector);
unsigned long		ft_vector_capacity(const t_vector *vector);
void				ft_vector_reserve(t_vector *vector,
						unsigned long new_capacity);
void				ft_vector_init(t_vector *vector);
void	*ft_realloc(void *ptr, size_t original_size, size_t new_size);
t_vector	*ft_vector_slice_left(t_vector *vector, unsigned long pos);
t_vector	*ft_vector_slice_right(t_vector *vector, unsigned long pos);

//remove at end
void	ft_print_ast(t_node	*root, char *branch);
#endif
