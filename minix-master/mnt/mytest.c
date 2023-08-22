#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#define RUN_N_PROCESSES 5
int main()
{
  struct timeval teststart,testend;
  gettimeofday(&teststart,NULL);
	int pid[20];
	int i,loops=9000;
	char processid[100],startc[100],endc[100];
    char filename[50];
    char processloops[10];
    sprintf(filename,"stdnSchedulerResults.txt");
    sprintf(startc,"%d",teststart.tv_sec);
    sprintf(endc,"%d",teststart.tv_usec);
    for(i=1;i<=RUN_N_PROCESSES;i++)
    {
        sprintf(processloops,"%d",(int)(0.7*(6-i)*loops));
    	pid[i]=fork(); 
        if(pid[i]==0)
    	{
    		sprintf(processid,"%d",i);
    		execlp("./longrun0","./longrun0",processid,filename,"90000",startc,endc,processloops,NULL);
        }
        
    }
    for(i=1;i<=RUN_N_PROCESSES;i++)
    {
        wait(NULL);
    }       
    gettimeofday(&testend,NULL);
   
  FILE *fptr;
  fptr = fopen(filename,"a");
  fprintf(fptr,"test took: %d.%06d\n", testend.tv_sec-teststart.tv_sec, abs(teststart.tv_usec-testend.tv_usec));
  fprintf(fptr,"______________________________________\n");
  fclose(fptr);


    return 0; 

}
