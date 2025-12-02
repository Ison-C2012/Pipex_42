#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	int	fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		perror("pipe")
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork")
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child(fd);
	waitpid();
}
