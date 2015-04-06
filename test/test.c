#include <stdio.h>
#include <stdlib.h>

#define PRIN 1
#ifdef PRIN
	#define DPRIN(name,args) printf(name,args)
#else 
	#define DPRIN(name,args) 
#endif

int main(void)
{
	DPRIN("%s","hello");
	return 0;
}
