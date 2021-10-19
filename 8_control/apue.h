#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <signal.h>
#define MAXLINE 512
#define exit(EXP)	return(EXP)
#define err_sys(...) { printf(__VA_ARGS__); \
	return -1;}
#define err_quit(...) { printf(__VA_ARGS__); \
	return -1;}
#define err_dump(...) { printf(__VA_ARGS__); \
	break ;}
#define err_ret(...) { printf(__VA_ARGS__); \
	return -1 ;}

void pr_exit(int status)
{
	if (WIFEXITED(status)) {
		printf("normal termination, exit status = %d\n",
				WEXITSTATUS(status));
	} else if (WIFSIGNALED(status)) {
		printf("abnormal termination, signal number = %d%s\n",
				WTERMSIG(status),
#ifdef WCOREDUMP
				WCOREDUMP(status) ? " (core file generated)" : "");
#else
				"");
#endif
	} else if (WIFSTOPPED(status)) { 
		printf("child stopped, signal number = %d\n",
				WSTOPSIG(status));
	}
}
