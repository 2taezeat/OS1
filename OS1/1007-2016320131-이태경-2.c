#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	
	pid = fork(); /*fork a child process*/

	if (pid < 0) /*error occurred*/
	{
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if (pid == 0) {/*child process*/
		execlp("/bin/ls", "ls", NULL); // version of the exec() system call
	}
	else { /*parent process*/
		wait(NULL); /*parent will wait for the child to complete*/
		printf("Child Complete");
	}
	return 0;
}
