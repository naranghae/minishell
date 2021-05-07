#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
    {
		printf("fork failed!\n");
		return (-1);
	}
	else if (pid == 0)
		printf("child_process: %i, pid: %d\n", getpid(), pid);
	else
	{
		printf("parent_process: %i\n", getpid());
		wait(NULL);
	}
	return (0);
}