
#ifndef IPC_H
#define IPC_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "../../../proj/includes/pipex.h"
#include "../../../proj/libft/includes/libft.h"
#include "../../../proj/libft/includes/ft_printf.h"

char	**get_paths_from_envp(char **ev);
void	free_arrs(char **arrs);


#endif

