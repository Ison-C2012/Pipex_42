#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main()
{
	int		fd[2];
	pid_t	pid;
	char	message[] = "Hey! It's time went to bed!";
	char	buffer[100];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		close(fd[1]);
		read(fd[0], buffer, sizeof(buffer));
		printf("Child received: %s\n", buffer);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		write(fd[1], message, sizeof(message));
		printf("Parent sent: %s\n", message);
		close(fd[1]);
		wait(NULL);
	}

	return 0;
}
