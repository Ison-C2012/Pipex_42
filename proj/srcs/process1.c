/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 22:26:17 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/04 01:13:56 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1(t_pipex *p, char *cmd1, char **ev)
{
	close(p->o_fd);
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

void	parent1(t_pipex *p)
{
	int	wstatus;

	close(p->p_fd[1]);
	if (waitpid(p->pid1, &wstatus, 0) == -1)
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
		parent1(p);
	return (success);
}
