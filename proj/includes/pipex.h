/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:58:59 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/05 18:35:08 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include "../libft/includes/libft_bonus.h"
# include "../libft/includes/ft_printf.h"

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# define SUCCESS 0
# define FAILURE 1
# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef enum s_bool
{
	error = -1,
	success,
	failure
}	t_bool;

typedef struct s_pipex
{
	char	*infile;
	char	*cmd1;
	char	*cmd2;
	char	*outfile;
	int		i_fd;
	int		o_fd;
	int		p_fd[2];
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

// pipex.c
int		pipex(char **av, char **ev);

// process.c
int		fork_process(t_pipex *p, char **ev, int p_nbr);

// exec.c
int		exec_command(char *cmd, char **ev);

//wait.c
int		wait_for_children(t_pipex *p);

//helper.c
bool	include_quote(char *str);
void	err_message(char *name, char *text);

#endif
