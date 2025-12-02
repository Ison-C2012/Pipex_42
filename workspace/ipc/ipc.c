#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve("/bin/ls", &argv[1], envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	waitpid(pid, &wstatus, 0);
	printf("connection success\n");
	return 0;
}
