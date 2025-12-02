# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# define READ  (0)
# define WRITE (1)

/**
 * @param *fd_r 読み込み用ファイルディスクリプタ
 * @param *fd_w 書き込み用ファイルディスクリプタ
 */

int	popen2(int *fd_r, int *fd_w)
{
	int	pipe_child2parent[2];
	int	pipe_parent2child[2];
	int	pid;

	if (pipe(pipe_child2parent) < 0)
	{
		perror("popen2.pipe");
		return 1;
	}

	if (pipe(pipe_parent2child) < 0)
	{
		perror("popen2.pipe");
		close(pipe_child2parent[READ]);
		close(pipe_child2parent[WRITE]);
		return 1;
	}

	if ((pid = fork()) < 0)
	{
		perror("popen2.fork");
		close(pipe_child2parent[READ]);
		close(pipe_child2parent[WRITE]);
		close(pipe_parent2child[READ]);
		close(pipe_parent2child[WRITE]);
		return 1;
	}

	if (pid == 0)
	{
		close(pipe_parent2child[WRITE]);
		close(pipe_child2parent[READ]);
		dup2(pipe_parent2child[READ], 0);
		dup2(pipe_child2parent[WRITE], 1);
		close(pipe_parent2child[READ]);
		close(pipe_child2parent[READ]);
		
		if (execl("./test1", "./test1", NULL) < 0)
		{
			perror("popen2.execl");
			close(pipe_parent2child[READ]);
			close(pipe_child2parent[WRITE]);
			return 1;
		}
	}

	close(pipe_parent2child[READ]);
	close(pipe_child2parent[WRITE]);

	*fd_r = pipe_child2parent[READ];
	*fd_w = pipe_parent2child[WRITE];

	return (pid);
}

/*
 input: hello
 output: test2:test1: hello
*/

int	main(int argc, char *argv[])
{
	int	fd_r = fileno(stdin);
	int	fd_w = fileno(stdout);

	if (argc < 2)
	{
		printf("Usage: %s <message>\n", argv[0]);
		return 1;
	}

	if (popen2(&fd_r, &fd_w) == 1)
		return 1;

	write(fd_w, argv[1], strlen(argv[1]));	//input: hello

	char	buf[255];
	int		size = read(fd_r, buf, 255);

	if (size == -1)
	{
		perror("error");
		return 1;
	}
	printf("test2:");
	fwrite(buf, 1, size, stdout);	//output: test1: hello
	printf("\n");
}
