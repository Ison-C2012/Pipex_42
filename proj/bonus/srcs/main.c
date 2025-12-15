/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:56:57 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/15 20:03:33 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_list	*create_cmdlst(char **cmd, int nbr)
{
	t_list	*cmdlst;
	t_list	*new;

	cmdlst = ft_lstnew(*cmd++);
	while (--nbr > 0)
	{
		new = ft_lstnew(*cmd++);
		if (new == NULL)
		{
			ft_lstclear(&cmdlst, free);
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back(&cmdlst, new);
	}
	return (cmdlst);
}

static void	init_pipex(t_pipex *p, char **av, int ac)
{
	p->infile = av[0];
	p->cmdlst = create_cmdlst(&av[1], ac - 2);
	p->outfile = av[ac - 1];
	p->p_fd[0] = -1;
	p->p_fd[1] = -1;
	p->status = IN;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	pid_t	pid;

	if (argc < 3)
		return (EXIT_FAILURE);
	init_pipex(&p, &argv[1], argc - 1);
	if (pipe(p.p_fd) == error)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}
	pid = fork_processes(&p, envp);
/*	p.pid1 = fork_process(&p, envp, 1);
	p.pid2 = fork_process(&p, envp, 2);
*/	close(p.p_fd[0]);
	close(p.p_fd[1]);
	return (wait_for_children(pid));
}
