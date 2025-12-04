/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 20:34:18 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/04 21:18:04 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	status_code(int status)
{
	int	code;

	if (WIFEXITED(status) == true)
		code = WEXITSTATUS(status);
	if (WIFSIGNALED(status) == true)
		code = WTERMSIG(status);
	if (WIFSIGNALED(status) == true)
	{
		code = WTERMSIG(status);
		if (WCOREDUMP(status) == true)
			return (-1);
	}
	return (code);
}

int	wait_for_child(t_pipex *p, pid_t pid)
{
	int     wstatus;

	if (waitpid(pid, &wstatus, 0) == -1)
	{
		perror("waitpid");
		close_fds(p);
		return (failure);
	}
	if (status_code(wstatus) != success)
	{
		close_fds(p);
		return (failure);
	}
	return (success);
}

int	wait_for_children(t_pipex *p)
{
	int	res1;
	int	res2;

	res1 = wait_for_child(p, p->pid1);
	res2 = wait_for_child(p, p->pid2);
	if (res1 != success || res2 != success)
		return (failure);
	return (success);
}

