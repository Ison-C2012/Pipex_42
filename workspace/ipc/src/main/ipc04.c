//$ ./ipc file cmd ..
//$ cmd .. file

#include "ipc.h"

void	parent(pid_t pid, int pipefd[])
{
	int		wstatus;
	int		stt;
	char	buf[1024];
	int		rd;

	close(pipefd[1]);
	if (waitpid(pid, &wstatus, 0) == -1)
	{
		perror("waitpid");
		close(pipefd[0]);
		exit(EXIT_FAILURE);
	}
	stt = interpret_status(wstatus);
//	printf("status: %d\t", wstatus);
//	printf("code: %d\n", interpret_status(wstatus));
	if (stt != success)
	{
		close(pipefd[0]);
		exit(EXIT_FAILURE);
	}
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
	close(pipefd[0]);
	printf("connection success\n");
}

void	child(char *file, char **cmd, char **ev, int pipefd[])
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

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (argc < 3)
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
		child(argv[1], &argv[2], envp, pipefd);
	else
		parent(pid, pipefd);
	return (success);
}
