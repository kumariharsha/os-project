#include<stdio.h>
#include<pthread.h>
#define MIN_PID 300
#define MAX_PID 5000

pthread_mutex_t l1;

struct pidValue
{
	int flag;
	int pid;
}p[4701];
int allocate_map(void)     //process id created
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

int allocate_pid(void)      //process id allocated
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

int release_pid(int pid)      //process id released
{
	int j=0;
	for(int i=MIN_PID;i<MAX_PID;i++)
	{
		if(p[j].pid==pid)
			p[j].flag==0;
			j++;
	}
}
void *crthread()
{
	int r=allocate_pid();
	pthread_mutex_lock(&l1);
	sleep(7);
	
	pthread_mutex_unlock(&l1);
	release_pid(r);
}

int main()
{
	pthread_t th[100];
	for(int i=0;i<100;i++)
	{
	pthread_create(&th[i],NULL,crthread,NULL);
	pthread_join(th[i],NULL);
    }
	
}
