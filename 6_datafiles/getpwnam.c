#include <pwd.h>
#include <stddef.h>
#include <string.h>

int main(int argc, char **name) {
	struct passwd * ptr;

	setpwent();
	while ((ptr = getpwent()) != NULL)
		if (strcmp(name, ptr->pw_name) == 0)
		break;
	endpwent();
	return(0);
}
