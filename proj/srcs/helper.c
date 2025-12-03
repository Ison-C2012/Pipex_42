/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:03:55 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/04 00:37:59 by keitotak         ###   ########.fr       */
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

void	free_arrs(char **arrs)
{
	char	**tmp;

	tmp = arrs;
	while (*arrs)
		free(*arrs++);
	free(tmp);
}

void	print_arrs(char **arrs)
{
	while (*arrs)
		ft_printf("%s\n", *arrs++);
}

