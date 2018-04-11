#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#define MIN_PID 300
#define MAX_PID 5000

pthread_mutex_t l1;
int t=1;

struct pidValue          //one structure created
{
	int flag;
	int pid;
}p[4701];
int allocate_map(void)     //allocation of values to data structure
{
	int j=0,i;
	printf("\nCreating data structure.\n");
	sleep(2);
	printf("Data Structure created\n\n");
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

int allocate_pid(void)      //allocation of PID to threads
{
	int j=0,i;
	printf("requesting a PID for process %d\n",t);
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

int release_pid(int pid)      //this function release PID
{
	int j=0,i;
	for(i=MIN_PID;i<MAX_PID;i++)
	{
		if(p[j].pid==pid)
			p[j].flag==0;
			j++;
	}
	printf("Releasing pid %d of process %d\n",pid,t);
}
void *crthread()                     //this function call other functions
{
	printf("Entering thread function\n");
	int r=allocate_pid();
	printf("PID %d allocated to process %d\n",r,t);
	t++;
	pthread_mutex_lock(&l1);           //mutex lock acquired
	sleep(2);
	
	pthread_mutex_unlock(&l1);         //mutex lock released
	release_pid(r);
	printf("PID released\n\n\n");
}

int main()
{
	pthread_t th[100];
	int i,n;
	printf("Enter no of thread u want to create:  ");
	scanf("%d",&n);             //threads entered by user
	allocate_map();
	for(i=0;i<n;i++)            //threads are created
	{
		printf("\nAllocation of PID to process %d started\n",i+1);
		pthread_create(&th[i],NULL,crthread,NULL);
		pthread_join(th[i],NULL);
    	}
}
