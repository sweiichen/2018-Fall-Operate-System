#include <stdio.h>
#include <unistd.h>
#include<string.h>
#include <stdlib.h>
#include <sys/types.h>


#define MAX_LINE 80
void readcomment(char inputBuffer[],char *arg[],int* background){
	int bytes;//the numbers of input bytes
	int str_index=1;//the number of the arg[]
	//int start=-1;
	*background = 0;
	//printf("!%d\n",background);
	//printf("?%d\n",*background);


	bytes=read(STDIN_FILENO, inputBuffer, MAX_LINE);
	//printf("%s\n",inputBuffer);
	if(bytes<0){
		exit(-1);
	}
	arg[0]=&inputBuffer[0];

	for(int i=1;i<bytes;i++){
		if(inputBuffer[i]==' '|inputBuffer[i]=='\t'){
			
			arg[str_index]=&inputBuffer[i+1];
			
			str_index++;
			inputBuffer[i]='\0';
			
		}
		else if(inputBuffer[i]=='\n'){
			
			arg[str_index]=NULL;
			
			inputBuffer[i]='\0';
			
		}
		
		if(inputBuffer[i]=='&'){
			*background=1;
			inputBuffer[i]='\0';
		}

		
	}


}

int main(void)
{
	char *arg[MAX_LINE/2+1]; /*command line arguments*/
	int should_run = 1; /*flag to determine when to exit program*/
	char inputBuffer[MAX_LINE];
	int background;
	int bytes;
	pid_t pid;
	while(should_run){
		printf("osh>");
		fflush(stdout);
		readcomment(inputBuffer, arg, &background);
		
		if(strcmp("exit",arg[0])==0){
			
			return 0;
		}
		
		

		pid=fork();
		
		if(pid==0){
			
			execvp(arg[0],arg);


		}
		
		else if(background==0){
			
			waitpid(pid);
			
		}
		else{
			//printf("osh>");;
		}

	


		/**
		* your code!
		* After reading user input, the step are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		* (3) if command included &, parent will not invoke wait()
		*/
	}

	return 0;
}

