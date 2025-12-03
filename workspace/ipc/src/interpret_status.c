#include "ipc.h"

int	interpret_status(int status)
{
	int	code;

	if (WIFEXITED(status) == true)
		code = WEXITSTATUS(status);
	if (WIFSIGNALED(status) == true)
		code = WTERMSIG(status);
	if (WIFSIGNALED(status) == true)
	{
		code = WTERMSIG(status);
		if (WCOREDUMP(status) == true)
			return (-1);
	}
	return (code);
}
