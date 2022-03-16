#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdarg.h>			//va_list
#include <sys/errno.h>		//errno
#define MAXLINE 512
#define exit(EXP)	return(EXP)
#define err_sys(...) { printf(__VA_ARGS__); \
	return -1;}
#define err_quit(...) { printf(__VA_ARGS__); \
	return -1;}
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

/*
 * Print a message and return to caller.
 * Caller specifies "errnoflag".
 */
static void
err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
	char	buf[MAXLINE];

	vsnprintf(buf, MAXLINE-1, fmt, ap);
	if (errnoflag)
		snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s",
		  strerror(error));
	strcat(buf, "\n");
	fflush(stdout);		/* in case stdout and stderr are the same */
	fputs(buf, stderr);
	fflush(NULL);		/* flushes all stdio output streams */
}

/*
 * Fatal error related to a system call.
 * Print a message, dump core, and terminate.
 */
void
err_dump(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
	abort();		/* dump core and terminate */
	_exit(1);		/* shouldn't get here */
}

