#include "ipc.h"

void	child(char **av, char **ev)
{
	char	*pathname;

	pathname = get_pathname(av[0], ev);
	if (pathname == NULL)
	{
		perror("get_pathname");
		exit(EXIT_FAILURE);
	}
	if (execve(pathname, av, ev) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	free(pathname);
	exit(EXIT_SUCCESS);
}

void	parent(pid_t pid)
{
	int		wstatus;

	waitpid(pid, &wstatus, 0);
	printf("connection success\n");
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;

	if (argc < 2)
		return (failure);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child(&argv[1], envp);
	else
		parent(pid);
	return 0;
}
