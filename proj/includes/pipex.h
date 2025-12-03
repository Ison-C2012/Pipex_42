/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:58:59 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/04 00:48:29 by keitotak         ###   ########.fr       */
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

typedef struct s_path
{
	char	**paths;
	char	**to_free;
	char	*path;
	char	*pathname;
}	t_path;

typedef struct s_pipex
{
	int		i_fd;
	int		o_fd;
	int		p_fd[2];
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

// pipex.c
int		pipex(char **av, char **ev);
void	close_fds(t_pipex *p);

// process1.c
int		process1(t_pipex *p, char *cmd1, char **ev);

// process2.c
int		process2(t_pipex *p, char *cmd2, char **ev);

// exec.c
int		exec_cmd(t_pipex *p, char *cmd, char **ev);

// helper.c
int		status_code(int status);
void	free_arrs(char **arrs);
void	print_arrs(char **arrs);

#endif
