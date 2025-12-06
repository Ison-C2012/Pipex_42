/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:56:57 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/06 11:16:29 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		ft_putendl_fd("\e[33mInvalid arguments.", 2);
		ft_putendl_fd("Usage: ./pipex file1 \"cmd1\" \"cmd2\" file2\e[0m", 2);
		return (EXIT_FAILURE);
	}
	if (include_quote(argv[2]) || include_quote(argv[3]))
	{
		ft_putstr_fd("\e[33m", 2);
		ft_putendl_fd("This program doesn't work with quotes in command.", 2);
		ft_putendl_fd("Please try commands without quotes.", 2);
		ft_putstr_fd("DOESN\'T WORK:\t", 2);
		ft_putstr_fd("./pipex file1 \"grep \'stdio\'\"", 2);
		ft_putendl_fd(" \"sed \'s/stdio/unistd/g\'\" file2\e[0m", 2);
		ft_putstr_fd("\e[32mDO WORK:\t./pipex file1 \"grep stdio\"", 2);
		ft_putendl_fd(" \"sed s/stdio/unistd/g\" file2\e[0m", 2);
		return (EXIT_FAILURE);
	}
	return (pipex(&argv[1], envp));
}
