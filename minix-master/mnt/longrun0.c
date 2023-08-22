/*
	I created my own longrun without the 'iteration and value' printf -- so as to avoid preemption during priority scheduler which gets 
	preempted during the above mentioned printf; it being an IO operation.
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <minix/endpoint.h>

#define LOOP_COUNT_MIN 10000
#define LOOP_COUNT_MAX 1000000
//takes 2 time vals, return the time delta in microsecs
long long subtime(struct timeval start,struct timeval end){
  return 1e6*(end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec);
}
int main (int argc, char *argv[])
{
  char *idStr;
  unsigned int	v;
  int	i = 0;
  int	iteration = 1;
  int	loopCount;
  int	maxloops;

  // if the passed parameters != 3 or 4 make alert and exit :params called in mytest (filepath(doesnt count),
  //filename[0] ,processid[1],filename[2], loop count[3], teststartsec[4],teststartusec[5],max loops[6],thisprocessloops[7],NULL)
  if (argc < 6 || argc > 7) 
  {
    printf ("Usage: %s <id> <loop count> [max loops]\n", argv[0]);
    exit (-1);
  }

  v = getpid ();

  idStr = argv[1];

  loopCount = atoi (argv[3]);
  int startsec= (time_t) atoi(argv[4]);
  int startusec= (time_t)atoi(argv[5]);
  if ((loopCount < LOOP_COUNT_MIN) || (loopCount > LOOP_COUNT_MAX)) 
  {
    printf ("%s: loop count must be between %d and %d (passed %s)\n", argv[0], LOOP_COUNT_MIN, LOOP_COUNT_MAX, argv[3]);
    exit (-1);
  }
  if (argc == 7) 
  {
    maxloops = atoi (argv[6]);
  } 
  else 
  {
    maxloops = 0;
  }

  struct timeval start,end,wait,curr; //store start, end (turnaround time) and temporary times for calculations
  double waiting_time=0; 
  start.tv_sec=startsec;
  start.tv_usec=startusec;
  // i initally 0
  //iterate for <max loops time> calculating waitng time
  while (1) 
  {
    if (++i == loopCount) 
    {
      if (iteration == maxloops) 
      {
		   break;
      }
      iteration += 1;
      i = 0;
    }
  }
  
  FILE *fptr;
  char *filename=argv[2];
   // use appropriate location if you are using MacOS or Linux
  double exetime=(1210/10000.0)*maxloops;
  fptr = fopen(filename,"a"); 
  gettimeofday(&end,NULL);
  waiting_time=abs((subtime(start,end)/1e3)-exetime);
  fprintf(fptr,"The process number %.1s, had Turnaround time = %0.6lf,Waiting time = %0.6lf  ms  process length= %0.6f\n\n", 
          idStr,subtime(start,end)/1e3,waiting_time,exetime);
  fclose(fptr);

}