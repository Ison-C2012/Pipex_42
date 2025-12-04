/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:56:57 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/05 01:37:25 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		ft_putendl_fd("\e[33mInvalid arguments.", 2);
		ft_putendl_fd("Usage: ./pipex file1 \"cmd1\" \"cmd2\" file2\e[0m", 2);
		return (failure);
	}
	if (pipex(&argv[1], envp) == failure)
		return (failure);
	return (success);
}
