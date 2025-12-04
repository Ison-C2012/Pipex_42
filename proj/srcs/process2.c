/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:26:59 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/04 10:10:46 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child2(t_pipex *p, char *cmd2, char **ev)
{
	close(p->p_fd[1]);
	p->o_fd = open(p->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->o_fd == error)
	{
		perror(p->outfile);
		close(p->p_fd[0]);
		exit(failure);
	}
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
		wait_for_child(p, p->pid2);
	return (success);
}
