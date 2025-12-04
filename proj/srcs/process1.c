/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 22:26:17 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/04 10:10:39 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1(t_pipex *p, char *cmd1, char **ev)
{
	close(p->p_fd[0]);
	p->i_fd = open(p->infile, O_RDONLY);
	if (p->i_fd == error)
	{
		perror(p->infile);
		close(p->p_fd[1]);
		exit(failure);
	}
	if (dup2(p->i_fd, STDIN) == error)
	{
		perror("dup2");
		close(p->i_fd);
		close(p->p_fd[1]);
		exit(failure);
	}
	if (dup2(p->p_fd[1], STDOUT) == error)
	{
		perror("dup2");
		close(p->i_fd);
		close(p->p_fd[1]);
		exit(failure);
	}
	exec_cmd(p, cmd1, ev);
}

int	process1(t_pipex *p, char *cmd1, char **ev)
{
	p->pid1 = fork();
	if (p->pid1 < 0)
	{
		perror("fork");
		close_fds(p);
		exit(failure);
	}
	if (p->pid1 == 0)
		child1(p, cmd1, ev);
	else
		wait_for_child(p, p->pid1);
	return (success);
}
