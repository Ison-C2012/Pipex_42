/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 22:26:17 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/04 21:33:53 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1(t_pipex *p, char *cmd1, char **ev)
{
//	close(p->o_fd);
	p->i_fd = open(p->infile, O_RDONLY);
	if (p->i_fd == error)
	{
		perror(p->infile);
		exit(failure);
	}
	close(p->p_fd[0]);
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

void	child2(t_pipex *p, char *cmd2, char **ev)
{
//	close(p->i_fd);
	p->o_fd = open(p->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->o_fd == error)
	{
		perror(p->outfile);
		exit(failure);
	}
	close(p->p_fd[1]);
	if (dup2(p->p_fd[0], STDIN) < 0)
	{
		perror("dup2");
		close(p->o_fd);
		close(p->p_fd[0]);
		exit(failure);
	}
	if (dup2(p->o_fd, STDOUT) < 0)
	{
		perror("dup2");
		close(p->o_fd);
		close(p->p_fd[0]);
		exit(failure);
	}
	exec_cmd(p, cmd2, ev);
}

int	process(t_pipex *p, char **ev, int p_nbr)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		close_fds(p);
		exit(failure);
	}
	if (pid == 0)
	{
		if (p_nbr == 1)
			child1(p, p->cmd1, ev);
		if (p_nbr == 2)
			child2(p, p->cmd2, ev);
	}
	return (pid);
}
