#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t newp(void);
int main()
{
	pid_t A,B,C;
	if ((A = newp()) == 0) printf("sciaobel\n");
	else{
			if ((B = newp()) == 0) printf("bellosciao\n");
			else{
					if ((C = newp()) == 0) printf("plswork\n");
						else{
								printf("vai col primo %d\n",wait(NULL));
								printf("vai col secondo %d\n",wait(NULL));
								printf("vai col terzo %d\n",wait(NULL));
								return 0;
							}}}

}

pid_t newp(void)
{
	pid_t temp = fork();
	if (temp < 0) abort();
	return temp;
}

