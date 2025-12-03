/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:26:59 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/04 01:05:52 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child2(t_pipex *p, char *cmd2, char **ev)
{
	close(p->i_fd);
	close(p->p_fd[1]);
	if (dup2(p->p_fd[0], STDIN) == error)
	{
		perror("dup2");
		close(p->o_fd);
		close(p->p_fd[0]);
		exit(failure);
	}
	if (dup2(p->o_fd, STDOUT) == error)
	{
		perror("dup2");
		close(p->o_fd);
		close(p->p_fd[0]);
		exit(failure);
	}
	exec_cmd(p, cmd2, ev);
}

void	parent2(t_pipex *p)
{
	int	wstatus;

	close(p->p_fd[0]);
	if (waitpid(p->pid2, &wstatus, 0) == -1)
	{
		perror("waitpid");
		close_fds(p);
		exit(failure);
	}
	if (status_code(wstatus) != success)
	{
		close_fds(p);
		exit(failure);
	}
}

int	process2(t_pipex *p, char *cmd2, char **ev)
{
	p->pid2 = fork();
	if (p->pid2 < 0)
	{
		perror("fork");
		close_fds(p);
		exit(failure);
	}
	if (p->pid2 == 0)
		child2(p, cmd2, ev);
	else
		parent2(p);
	return (success);
}
