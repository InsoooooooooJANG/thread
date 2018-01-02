//thread
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_THREADS (10)
int STotal = 0;
void *t_function(void* data);

//쓰레드에서 사용할 함수
void *t_function(void* data)
{
  STotal += *((int*)data);

  return (void*)(*((int*)data));
}

int main(void)
{
  int cntOfThread = 0;
  int thr_id, i;
  int Total = 0;
  int Result = 0;
  int status=0;
  int data[MAX_THREADS]; 

  pthread_t p_thread[MAX_THREADS]; 
  
  while(1)
  {
    if(cntOfThread == MAX_THREADS)
    {
      printf("MAXIMUM THREAD NUMBER : %d\n", cntOfThread);
      break;
    }

    data[cntOfThread] = cntOfThread;       

    thr_id = pthread_create(&p_thread[cntOfThread], NULL, t_function, (void*)&data[cntOfThread]);
    
    if(thr_id < 0)
    {
      printf("pthread_create returns error[%d]\n", thr_id);
      return -1;
    }

    cntOfThread++;
  }

  for(i=0; i<cntOfThread; i++)
  {
    pthread_join(p_thread[i], (void*)&status);

    Total += status;
  }

  printf(" Total :: %d\n", Total);
  printf("STotal :: %d\n", STotal);

  return 0;
} 
