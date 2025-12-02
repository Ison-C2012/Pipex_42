#include "ipc.h"

char	*get_pathname(char *name, char **ev)
{
	char	**paths;
	char	*path;
	char	*pathname;
	char	**paths_to_free;

	paths = get_paths_from_envp(ev);
	if (paths == NULL)
		return (NULL);
	paths_to_free = paths;
	while (*paths != NULL)
	{
		path = ft_strjoin(*paths, "/");
		if (path == NULL)
			return (NULL);
		pathname = ft_strjoin(path, name);
		if (pathname == NULL)
			return (NULL);
		free(path);
		if (access(pathname, X_OK) == 0)
			break ;
		free(pathname);
		*paths++;
	}
	if (paths == NULL)
		pathname = NULL;
	free_arrs(paths_to_free);
	return (pathname);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		wstatus;
	char	*pathname;

	if (argc < 2)
		return (failure);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		pathname = get_pathname(argv[1], envp);
		if (pathname == NULL)
		{
			perror("get_pathname");
			exit(EXIT_FAILURE);
		}
		if (execve(pathname, &argv[1], envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	waitpid(pid, &wstatus, 0);
	printf("connection success\n");
	return 0;
}
