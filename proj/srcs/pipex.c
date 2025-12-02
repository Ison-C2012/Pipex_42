/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:07:47 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/02 12:47:43 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

typedef struct s_pipex
{
	int		i_fd;
	int		o_fd;
	int		p_fd[2];
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

int	open_iofile(t_pipex *p, char *infile, char *outfile)
{
	p->i_fd = open(infile, O_RDONLY);
	if (p->i_fd == -1)
		return (failure);
	p->i_fd = open(outfile, O_WRONLY);
	if (p->o_fd == -1)
		return (failure);
	return (success);
}

void	close_fds(t_pipex *p)
{
	close(p.i_fd);
	close(p.o_fd);
	close(p.p_fd[0]);
	close(p.p_fd[1]);
}

int	pipex(char **av, char **ev)
{
	t_pipex	p;

	if (open_iofile(&p, av[0], av[3]) == failure)
		return (failure);
	if (pipe(p.p_fd) == -1)
	{
		close_fds(p);
		return (failure);
	}
	p.pid = fork();
	if (p.pid == -1)
	{
		close_fds(p);
		return (failure);
	}
	if (p.pid == 0)
	{

	}
}
