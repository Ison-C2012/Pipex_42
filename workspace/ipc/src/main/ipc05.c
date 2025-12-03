//$ ./ipc file1 cmd1 cmd2 file2
//$ < file1 cmd1 | cmd2 file2

#include "ipc.h"

void	child1(char *file, char **cmd, char **ev, int pipefd[])
{
	int		fd;
	char	*pathname;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN) == -1)
	{
		perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT) == -1)
	{
		perror("dup2");
		close(fd);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	pathname = get_pathname(cmd[0], ev);
	if (pathname == NULL)
	{
		perror("get_pathname");
		close(fd);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	if (execve(pathname, cmd, ev) == -1)
	{
		perror("execve");
		close(fd);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	free(pathname);
	close(fd);
	exit(EXIT_FAILURE);
}

void	parent_c1(pid_t pid, int pipefd[])
{
	int		wstatus;
	int		stt;

	if (waitpid(pid, &wstatus, 0) == -1)
	{
		perror("waitpid");
		close(pipefd[0]);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	stt = interpret_status(wstatus);
	if (stt != success)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (argc != 5)
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
		child1(argv[1], &argv[2], envp, pipefd);
	else
		parent_c1(pid, pipefd);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child2(argv[3], &argv[4], envp, pipefd);
	else
		parent(pid, pipefd);

	return (success);
}
