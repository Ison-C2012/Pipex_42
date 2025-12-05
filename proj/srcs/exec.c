/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:11:26 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/05 15:55:30 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#define PATH "PATH="

static char	**get_paths_from_envp(char **ev)
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

static void	free_arrs(char **arrs)
{
	char	**tmp;

	tmp = arrs;
	while (*arrs)
		free(*arrs++);
	free(tmp);
}

static char	*free_path(char *path, char **paths)
{
	free(path);
	free_arrs(paths);
	return (NULL);
}

static char	*get_pathname(char *name, char **ev)
{
	t_path	pt;

	pt.paths = get_paths_from_envp(ev);
	if (pt.paths == NULL)
		return (NULL);
	pt.to_free = pt.paths;
	while (*pt.paths != NULL)
	{
		pt.path = ft_strjoin(*pt.paths, "/");
		if (pt.path == NULL)
			return (free_path(pt.path, pt.to_free));
		pt.pathname = ft_strjoin(pt.path, name);
		if (pt.pathname == NULL)
			return (free_path(pt.path, pt.to_free));
		if (access(pt.pathname, X_OK) == success)
			break ;
		free(pt.path);
		free(pt.pathname);
		pt.paths++;
	}
	if (pt.paths == NULL)
		return (free_path(pt.path, pt.to_free));
	free_arrs(pt.to_free);
	return (pt.pathname);
}

int	exec_command(char *cmd, char **ev)
{
	char	**cmdset;
	char	*pathname;

	cmdset = ft_split(cmd, ' ');
	if (cmdset == NULL)
		return (failure);
	pathname = get_pathname(cmdset[0], ev);
	if (pathname == NULL)
	{
		free_arrs(cmdset);
		return (failure);
	}
	if (execve(pathname, cmdset, ev) == -1)
	{
		ft_putstr_fd(cmdset[0], 2);
		ft_putendl_fd(": command not found", 2);
		free_arrs(cmdset);
		return (failure);
	}
	return (failure);
}
