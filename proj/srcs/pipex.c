/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:07:47 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/04 09:48:39 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//av[0]:infile
//av[1]:cmd1
//av[2]:cmd2
//av[3]:outfile

int	pipex(char **av, char **ev)
{
	t_pipex	p;

	p.infile = av[0];
	p.outfile = av[3];
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
