#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	const int	BUF_LEN = 255;
	char		buf[BUF_LEN];
	int			rc;

	rc = read(STDIN_FILENO, buf, BUF_LEN);
	if (rc < 0)
	{
		perror("read");
		return 1;
	}

	printf("test1: ");
//	write(STDOUT_FILENO, buf, rc);
	fwrite(buf, 1, rc, stdout);

	return 0;
}
