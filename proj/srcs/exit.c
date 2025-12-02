/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:01:55 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/01 17:34:30 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_pipex_exp(void)
{
	ft_putendl_fd("", 1);
	ft_putendl_fd("\e[37m+=============  Pipex Usage  =============+\e[0m", 1);
	ft_putendl_fd("\nPipex behaves like the following shell command:", 1);
	ft_putendl_fd("\t$ < file1 cmd1 | cmd2 > file2\n", 1);
	ft_putendl_fd("Usage example:\t./pipex file1 <cmd1> <cmd2> file2", 1);
	ft_putendl_fd("\e[32m\t$ ./pipex infile \"ls -l\" \"wc -l\" outfile", 1);
	ft_putendl_fd("\e[0m", 1);
}

void	invalid_args(void)
{
	ft_putendl_fd("", 2);
	ft_putendl_fd("\e[31m+==========  Invalid Arguments  ==========+", 2);
	ft_putstr_fd("\nPlease see the following explanation and retry.\e[0m\n", 2);
	print_pipex_exp();
	exit(EXIT_FAILURE);
}

