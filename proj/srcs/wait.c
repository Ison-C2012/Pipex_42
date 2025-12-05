/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 20:34:18 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/05 11:47:02 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	status_code(int status)
{
	int	code;

	if (WIFEXITED(status))
		code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		code = WTERMSIG(status);
	if (WIFSIGNALED(status))
	{
		code = WTERMSIG(status);
		if (WCOREDUMP(status))
			return (-1);
	}
	return (code);
}

static int	wait_for_child(pid_t pid)
{
	int	wstatus;

	if (waitpid(pid, &wstatus, 0) == error)
		return (failure);
	if (status_code(wstatus) != success)
		return (failure);
	return (success);
}

int	wait_for_children(t_pipex *p)
{
	int	res1;
	int	res2;

	res1 = wait_for_child(p->pid1);
	res2 = wait_for_child(p->pid2);
	if (res1 != success || res2 != success)
		return (failure);
	return (success);
}
