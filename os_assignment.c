#include<stdio.h>
#include<pthread.h>
#define MIN_PID 300
#define MAX_PID 5000

pthread_mutex_t l1;         

struct pidValue             //one structure is declared having two 
{
	int flag;
	int pid;
}p[4701];
int allocate_map(void)     //this function allocates values to data structure 
{
	int j=0,i;
	printf("Creating data structure.\n");
	for(i=MIN_PID;i<=MAX_PID;i++)
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

int allocate_pid(void)      // this function allocates process id 
{
	int j=0,i;
	printf("allocating pid to process\n");
	for(i=MIN_PID;i<=MAX_PID;i++)
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

int release_pid(int pid)      //this function release process id 
{
	int j=0,i;
	for(i=MIN_PID;i<MAX_PID;i++)
	{
		if(p[j].pid==pid)
			p[j].flag==0;
			j++;
	}
	printf("Releasing pid %d",pid);
}
void *crthread()              //this function create,allocate and release pid
{
	printf("Entering thread function\n");
	int r=allocate_pid();
	printf("PID allocated\n");
	pthread_mutex_lock(&l1);             //mutex lock acquired
	sleep(7);
	
	pthread_mutex_unlock(&l1);           //mutex lock released
	release_pid(r);
	printf("PID released\n");
}

int main()
{
	pthread_t th[100];
	int i;
	allocate_map();
	for(i=0;i<100;i++)                //threads are created
	{
		printf("Allocating PID to thread %d",i+1);
	pthread_create(&th[i],NULL,crthread,NULL);
	pthread_join(th[i],NULL);
    }
}
