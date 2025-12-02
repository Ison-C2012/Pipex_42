#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve("/bin/ls", "ls", envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	waitpid();
}
