#include<stdio.h>
#define MIN_PID 300
#define MAX_PID 5000

struct pidValue
{
	int flag;
	int pid;
}p[4701];
int allocate_map(void)
{
	int j=0;
	for(int i=MIN_PID;i<=MAX_PID;i++)
	{
		p[j].pid=i;
		p[j].flag=0;
		j++;
	}
	if(j!=4700)
	return -1;
	
	else
	return 1;
}

int allocate_pid(void)
{
	int j=0;
	for(int i=MIN_PID;i<=MAX_PID;i++)
	{
		if(p[j].flag==0)
		{
			p[j].flag=1;
			return i;
		}
		j++;
	}
	return -1;	
}

int release_pid(int pid)
{
	int j=0;
	for(int i=MIN_PID;i<MAX_PID;i++)
	{
		if(p[j].pid==pid)
			p[j].flag==0;
			j++;
	}
}


int main()
{
	
}
