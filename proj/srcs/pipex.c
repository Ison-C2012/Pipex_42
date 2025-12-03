/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:07:47 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/03 21:36:17 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(t_pipex *p)
{
	close(p.i_fd);
	close(p.o_fd);
	close(p.p_fd[0]);
	close(p.p_fd[1]);
}

int	open_iofile(t_pipex *p, char *infile, char *outfile)
{
	p->i_fd = open(infile, O_RDONLY);
	if (p->i_fd == error)
	{
		perror(infile);
		exit(EXIT_FAILURE);
	}
	p->i_fd = open(outfile, O_WRONLY);
	if (p->o_fd == error)
	{
		close(p->i_fd);
		perror(outfile);
		exit(EXIT_FAILURE);
	}
	return (success);
}

//av[0]:infile
//av[1]:cmd1
//av[2]:cmd2
//av[3]:outfile

int	pipex(char **av, char **ev)
{
	t_pipex	p;

	open_iofile(&p, av[0], av[3]);

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
