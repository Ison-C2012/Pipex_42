/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:56:57 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/12 11:34:32 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

typedef struct s_lstcmd
{
	char			*name;
	char			*path;
	char			*pathname;
	struct s_lstcmd	*next;
}	t_lstcmd;

t_lstcmd	*new_lstcmd(char *name)
{
	t_lstcmd	*new;

	new = (t_lstcmd *)malloc(sizeof(t_lstcmd));
	if (new == NULL)
		return (NULL);
	new->name = name;
	return (new);
}

t_lstcmd	*get_lstcmd(char ***av, int count)
{
	t_lstcmd	*cmds;
	t_lstcmd	*res;

	cmds = new_lstcmd(**av++);
	if (cmds == NULL)
		return (NULL);
	res = cmds;
	while (--count)
	{
		cmds->next = new_lstcmd(**av++);
		cmds = cmds->next;
	}
	return (res);
}

static void	init_pipex(t_pipex *p, char **av, int ac)
{
	p->infile = *av;
	p->cmds = get_lstcmd(&av[1], ac - 1);
	p->outfile = *av;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;

	if (argc < 3)
		return (EXIT_FAILURE);
	init_pipex(&p, &argv[1], argc - 1);
	if (pipe(p.p_fd) == error)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}
/*
	p.pid1 = fork_process(&p, envp, 1);
	p.pid2 = fork_process(&p, envp, 2);
*/	close(p.p_fd[0]);
	close(p.p_fd[1]);
	return (wait_for_children(&p));
}
