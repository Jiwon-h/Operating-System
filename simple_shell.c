#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LEN 100 /* The maximum length command */

int main(void) {
	char *args[MAX_LEN / 2 + 1]; /* command line arguments */
	int should_run = 1;          /* flag to determine when to exit program */
	int background = 0;
  //	char *input;
  //	int status;
	//input=(char*)malloc(MAX_LEN*sizeof(char));
 
  	while(should_run){
    	printf("my_shell> ");
    	fflush(stdout);
    	/**
     	* 표준입출력으로부터 문자열을 입력 받은 후:
     	* (1) fork()를 통해 자식 프로세스를 생성
     	* (2) 자식 프로세스가 execvp()를 호출하도록 할 것
     	* (3) 만약 입력받은 문자에 &가 포함되어 있으면,
     	*     부모 프로세스는 wait() 호출하지 않음
     	*/
	
	

	char *input = (char*)malloc(MAX_LEN*sizeof(char));
    	memset(args,0,MAX_LEN / 2 + 1);//initialize input vector
    	fgets(input, MAX_LEN, stdin);//#1 put the value to string 
	input[strlen(input)-1]='\0';	
	
//	printf("#1");
    	
	if(*input=='\0') //#2 GOTO EMPTY
   	{	
		goto EMPTY_VEC;
    	}

	int i=0;
	args[i]=strtok(input, " \n");
//	printf("#2");
	while(args[i]!=NULL) //#2 split string
	{	
		i++;
		args[i]=strtok(NULL, " \n");	
	}
	
	//char *arg=malloc((i)*sizeof(char*));
	if(strcmp(args[0],"exit")==0) //#3 compare string
	{
		//goto EMPTY_VEC;
		break;
	}
	if(strcmp(args[i-1],"&")==0)
	{
		args[i-1]=NULL;
		background=1;
	}
	

	int status;
	pid_t pid=fork(); //#4  make child process using fork()
	
	if(pid<0) // error handling
	{
		perror("pid is negative\n");
		exit(0);
	}
	if(pid==0)//execute child process
	{
//		printf("pid is zero. execute child process\n");
		execvp(args[0],args);
	}
	if(pid>0) // pid is positive. execute parent process.
	{	
		if(!background)
		{
			printf("wating for child, not  a background process\n");
			waitpid(pid,&status,0);
			printf("child process complete \n");
		}
		else
		{	printf("background process\n");
			background = 0;
		}
	}
	
	EMPTY_VEC: 
		free(input);	
	
  }
  return 0;
}
