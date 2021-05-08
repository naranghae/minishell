#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	char buf[1024];

	if (ac != 2)
		return (0);
	printf("dir name: %s\n", av[1]);
	printf("before dir: %s\n", getcwd(buf, 1024));
	if(chdir(av[1]) == -1)
		printf("failed, cd\n");
	else
		printf("after dir: %s\n", getcwd(buf, 1024));
	return (0);
}
