/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:03:55 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/04 09:55:57 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(t_pipex *p)
{
	close(p->i_fd);
	close(p->o_fd);
	close(p->p_fd[0]);
	close(p->p_fd[1]);
}

void	print_arrs(char **arrs)
{
	while (*arrs)
		ft_printf("%s\n", *arrs++);
}
