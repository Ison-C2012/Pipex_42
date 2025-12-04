#include <unistd.h>

int	main(void)
{
	if (close(5) == -1)
		return 1;
	return 0;
}
