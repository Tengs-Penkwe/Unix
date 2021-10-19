#include "apue.h"

int global_var = 88;

int child_vfork() {
	printf("Inside sub-function\n");
	
	pid_t pid;
	if ((pid = fork()) < 0) {
		perror("vfork error\n");
	} else if (pid == 0) {
		global_var ++;
	}

	return 66;
}


int main() {
	printf("main begins\n");

	int main_var = 8;

	int ret = child_vfork();
	printf("back to main\n");
	printf("global_var = %d, main_var = %d, ret = %d\n", global_var, main_var, ret);
	
	_exit(126);
}
