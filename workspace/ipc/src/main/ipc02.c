#include "ipc.h"

void	child(char **av, char **ev, int pipefd[])
{
	char	*pathname;

	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT) == -1)
	{
		perror("dup2");
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
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

void	parent(pid_t pid, int pipefd[])
{
	int		wstatus;
	char	buf[1024];
	int		rd;

	close(pipefd[1]);
	waitpid(pid, &wstatus, 0);
	rd = 1;
	while (rd == 1)
	{
		rd = read(pipefd[0], buf, 1);
		if (rd == -1)
		{
			perror("read");
			close(pipefd[0]);
			exit(EXIT_FAILURE);
		}
		if (write(STDOUT, buf, 1) == -1)
		{
			perror("write");
			close(pipefd[0]);
			exit(EXIT_FAILURE);
		}
	}
	printf("\nconnection success\n");
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (argc < 2)
		return (failure);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child(&argv[1], envp, pipefd);
	else
		parent(pid, pipefd);
	return success;
}
