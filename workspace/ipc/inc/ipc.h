#ifndef IPC_H
#define IPC_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "../../../proj/includes/pipex.h"
#include "../../../proj/libft/includes/libft.h"
#include "../../../proj/libft/includes/ft_printf.h"

#define STDIN 0
#define STDOUT 1

char	**get_paths_from_envp(char **ev);
char	*get_pathname(char *name, char **ev);
void	free_arrs(char **arrs);
int		interpret_status(int status);

#endif
