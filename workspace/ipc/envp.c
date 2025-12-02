/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:54:12 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/02 17:46:41 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ipc.h"

#define PATH "PATH="

void	print_arrs(char **arrs)
{
	while (*arrs)
		ft_printf("%s\n", *arrs++);
}

void	free_arrs(char **arrs)
{
	char	**tmp;

	tmp = arrs;
	while (*arrs)
		free(*arrs++);
	free(tmp);
}

char	**get_paths_from_envp(char **ev)
{
	char	**paths;

	while (*ev != NULL)
	{
		if (ft_strncmp(PATH, *ev, ft_strlen(PATH)) == 0)
		{
			paths = ft_split(*ev + ft_strlen(PATH), ':');
			return (paths);
		}
		ev++;
	}
	return (NULL);
}

/*
int	main(int argc, char *argv[], char *envp[])
{
	char	**paths;

	print_arrs(envp);
	paths = get_paths_from_envp(envp);
	if (paths == NULL)
		return (1);
	print_arrs(paths);
	free_arrs(paths);
	return 0;
}
*/
