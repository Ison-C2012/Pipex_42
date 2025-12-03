/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:07:47 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/04 00:57:09 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_iofile(t_pipex *p, char *infile, char *outfile)
{
	p->i_fd = open(infile, O_RDONLY);
	if (p->i_fd == error)
	{
		perror(infile);
		exit(failure);
	}
	p->o_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->o_fd == error)
	{
		close(p->i_fd);
		perror(outfile);
		exit(failure);
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

//av[0]:infile
//av[1]:cmd1
//av[2]:cmd2
//av[3]:outfile

int	pipex(char **av, char **ev)
{
	t_pipex	p;

	open_iofile(&p, av[0], av[3]);
	if (pipe(p.p_fd) == error)
	{
		perror("pipe");
		close(p.i_fd);
		close(p.o_fd);
		exit(failure);
	}
	process1(&p, av[1], ev);
	process2(&p, av[2], ev);
	close_fds(&p);
	return (success);
}
