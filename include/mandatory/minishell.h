/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:25:14 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/05 15:37:13 by ishenriq         ###   ########.fr       */
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
# inclide <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../lib/libft/libft.h"
# include "../lib/printf/ft_printf.h"
# include "../lib/libft/gnl/get_next_line.h"

#endif
