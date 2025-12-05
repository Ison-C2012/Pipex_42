/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 20:34:18 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/05 20:40:14 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	status_code(int status)
{
	int	code;

	if (WIFEXITED(status))
		code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		code = WTERMSIG(status) + 128;
	return (code);
}

int	wait_for_children(t_pipex *p)
{
	int	code;
	int	wstatus;

	if (waitpid(p->pid1, NULL, 0) == error)
	{
		perror("waitpid");
		return (failure);
	}
	if (waitpid(p->pid2, &wstatus, 0) == error)
	{
		perror("waitpid");
		return (failure);
	}
	code = status_code(wstatus);
	return (code);
}
