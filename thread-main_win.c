#include<stdio.h>
#include<windows.h>

#define MAX_THREADS (10)
DWORD STotal = 0;
DWORD WINAPI ThreadProc(LPVOID lpParam);

int main(int argc,char *argv[]){
  DWORD cntOfThread=0;
  DWORD dwThreadID[MAX_THREADS];
  HANDLE hThread[MAX_THREADS];
  DWORD Total =0;
  DWORD Result=0;
  DWORD i;

  //while문을 이용하여 10개의 스레드 생성
  while(1)
  {
    if(cntOfThread == MAX_THREADS)
    {
      printf("MAXIMUM THREAD NUMBER : %d\n" ,cntOfThread);
      break;
    }

    hThread[cntOfThread] = CreateThread ( NULL, 0,ThreadProc, (LPVOID)cntOfThread,0, &dwThreadID[cntOfThread]); 
    
    if ( hThread[cntOfThread] == NULL )
    {
      DWORD j;
      for(j = 0; j < cntOfThread; j++)
      {
        CloseHandle(hThread[j]);
        printf("failte to create thread\n");
        return -1;
      }
    }
    
    cntOfThread++;
  } 

  //스레드가 모두 리턴 시그널을 반환할 때까지 기다림
  WaitForMultipleObjects( MAX_THREADS, hThread, TRUE, INFINITE ); 

  for(i=0; i<cntOfThread; i++)
  {
    GetExitCodeThread(hThread[i],&Result);

    if(Result == 129) // 129 에러 -> WaitForMultipleObjects 함수의 첫 번째 인자를 생성한 스레드 개수와 맞지 않음
    {
      printf("first parameter of WaitForMultipleObjects is wrong data");
      return -1;
    }

    Total += Result;
    CloseHandle(hThread[i]);
  }

  printf( " Total :: %d \n", Total);      //스레드의 리턴값으로 얻은 Total
  printf( "STotal :: %d \n", STotal);   //스레드가 전역변수에 접근하여 계산된 값
  return 0;
  }

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
  STotal += (DWORD)lpParam; // 전역변수도 접근 가능
  return (DWORD)lpParam;      // 리턴값       전달 가능
}
