#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void signalhandler(int);
pid_t newp(void);

int main()
{
	printf("\neeeeyyy\n");
	signal(SIGINT,SIG_IGN);
	pid_t A = newp();
	printf("\neyyyaaa\n");
	if (A == 0)
	{
		signal(SIGINT,signalhandler);
		for (int i=0;i<500;i++)
		{
			printf("\nayy\n");
			sleep(1);
		}
		exit(0);
	}
	
	wait(NULL);
	return 6;
}

pid_t newp()
{
	pid_t tmp = fork();
	if (tmp < 0) abort();
	return tmp;

}

void signalhandler(int signo)
{
	pid_t tmp = newp();
	if (tmp == 0)
	execlp("ls","",NULL);
}
