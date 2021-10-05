#include "apue.h"

int main(void)
{
	char* this;
	char* that = tmpnam(this);
	
	printf("%s\n",this);
	printf("%s\n",that);

}
