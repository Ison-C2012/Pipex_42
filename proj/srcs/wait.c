/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:26:39 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/04 09:27:31 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	status_code(int status)
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

void	wait_for_child(t_pipex *p, int pid)
{
	int	wstatus;

	if (waitpid(pid, &wstatus, 0) == -1)
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
