#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
int main(void){
	pid_t pid;
	int mom,kid1,kid2,kid3,kid4,kid5;
	int id;
	mom=getpid();
	printf("Main process id : %d.\n",mom );

	pid=fork();	//fork1

	
	if(pid>0){
		kid1=pid;
		printf("Fork1,I'm the child %d, my parent is %d.\n",kid1,mom );
		id=getpid();
		wait(NULL);
		
	
	}
	else if(pid<0){
		printf("Error");
	}
	else if(pid==0){
		pid=fork();//fork2;
		if(pid>0){
			
			printf("Fork2,I'm the child %d, my parent is %d.\n",pid,getpid());
			id=getpid();
			wait(NULL);
			
		}
		else if(pid==0){
			id=getpid();
		}
	}
	else ;
	pid=fork();//fork3

	if(pid>0){
		kid3=pid;

		printf("Fork3,I'm the child %d, my parent is %d.\n",kid3,id);
		wait(NULL);
		exit(0);

	}
	return 0;
}