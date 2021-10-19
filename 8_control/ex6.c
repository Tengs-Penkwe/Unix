#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define STATUS_SIZE 256

int main(void)
{
    pid_t pid;
    int status;

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    /* Child */
    if (pid == 0)
        exit(0);

    /* Parent
     * Gives you time to observe the zombie using ps(1) ... */
//	char* status_info = (char*)malloc(256 * sizeof(char));
		system("ps -al");
//	printf("%s", status_info);
    sleep(5);

    /* ... and after that, parent wait(2)s its child's
     * exit status, and prints a relevant message. */
    pid = wait(&status);
    if (WIFEXITED(status))
        fprintf(stderr, "\n\t[%d]\tProcess %d exited with status %d.\n",
                (int) getpid(), pid, WEXITSTATUS(status));

    return 0;
}
