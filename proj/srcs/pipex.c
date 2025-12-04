/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:07:47 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/04 21:19:50 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_iofile(t_pipex *p, char *infile, char *outfile)
{
	p->i_fd = open(infile, O_RDONLY);
	if (p->i_fd == error)
	{
		perror(infile);
		return (failure);
	}
	p->o_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->o_fd == error)
	{
		close(p->i_fd);
		perror(outfile);
		return (failure);
	}
	return (success);
}

void	close_fds(t_pipex *p)
{
	close(p->i_fd);
	close(p->o_fd);
	close(p->p_fd[0]);
	close(p->p_fd[1]);
}

void	init_pipex(t_pipex *p, char **av)
{
	p->infile = av[0];
	p->cmd1 = av[1];
	p->cmd2 = av[2];
	p->outfile = av[3];
	open_iofile(p, av[0], av[3]);
}

int	pipex(char **av, char **ev)
{
	t_pipex	p;

	init_pipex(&p, av);
	if (pipe(p.p_fd) == error)
	{
		perror("pipe");
		close(p.i_fd);
		close(p.o_fd);
		return (failure);
	}
	p.pid1 = process(&p, ev, 1);
	p.pid2 = process(&p, ev, 2);
	close_fds(&p);
	if (wait_for_children(&p) == failure)
		return (failure);
	return (success);
}
