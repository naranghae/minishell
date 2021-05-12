#include <stdio.h>
#include <unistd.h>

int	main()
{
	char *tty;
	if (isatty(0)){
		tty = ttyname(0);
		printf("%s\n", tty);
	}
	else {
		printf("not tty\n");
	}
}