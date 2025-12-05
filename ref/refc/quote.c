#include <stdio.h>
#include <stdlib.h>

char	**ft_split(char *str, char c);

int	main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	printf("%s %s\n", av[0], av[1]);
	char **ss = ft_split(av[1], ' ');
	char **tmp = ss;
	while (*ss)
		printf("%s\n", *ss++);
	ss = tmp;
	while (*tmp)
		free(*tmp++);
	free(ss);
	return 0;
}
