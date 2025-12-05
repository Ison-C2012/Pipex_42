/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 22:26:17 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/05 11:56:32 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child1(t_pipex *p, char **ev)
{
	close(p->p_fd[0]);
	p->i_fd = open(p->infile, O_RDONLY);
	if (p->i_fd == error)
	{
		perror(p->infile);
		close(p->p_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (dup2(p->i_fd, STDIN) == error)
	{
		perror("dup2");
		close(p->i_fd);
		close(p->p_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (dup2(p->p_fd[1], STDOUT) == error)
	{
		perror("dup2");
		close(p->i_fd);
		close(p->p_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (exec_command(p->cmd1, ev) == EXIT_FAILURE)
	{
		close(p->i_fd);
		close(p->p_fd[1]);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

static void	child2(t_pipex *p, char **ev)
{
	close(p->p_fd[1]);
	p->o_fd = open(p->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->o_fd == error)
	{
		perror(p->outfile);
		exit(EXIT_FAILURE);
	}
	if (dup2(p->p_fd[0], STDIN) < 0)
	{
		perror("dup2");
		close(p->o_fd);
		close(p->p_fd[0]);
		exit(EXIT_FAILURE);
	}
	if (dup2(p->o_fd, STDOUT) < 0)
	{
		perror("dup2");
		close(p->o_fd);
		close(p->p_fd[0]);
		exit(EXIT_FAILURE);
	}
	if (exec_command(p->cmd2, ev) == EXIT_FAILURE)
	{
		close(p->o_fd);
		close(p->p_fd[0]);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int	fork_process(t_pipex *p, char **ev, int p_nbr)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		close(p->p_fd[0]);
		close(p->p_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (p_nbr == 1)
			child1(p, ev);
		if (p_nbr == 2)
			child2(p, ev);
	}
	return (pid);
}
