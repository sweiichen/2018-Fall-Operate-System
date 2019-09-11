#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#define NUMBER_OF_THREADS 11 /* Hint */
#define PUZZLE_SIZE 9
int rv;

/* example puzzle */
int puzzle[PUZZLE_SIZE+1][PUZZLE_SIZE+1] = {
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0}
		};

/* data structure for passing data to threads */
typedef struct
{
	int thread_number;
	int x;
	int y;
} parameters;

/* print puzzle */ 
#define LINE "====================== \n"
#define COLLINE "\n___________________________________ \n"
#define NAME "||  SUM   CHECKER  || \n"
void print_grid(int grid[10][10])
{
    int i,j;
    printf(LINE);
    printf(NAME);
    printf(LINE);

	for (i = 1; i < 10; i++)
	{
		for (j = 1; j < 10; j++)
		{
	        printf("|%1d |",grid[i][j]);
		}
        printf(COLLINE);
	}
    printf("\n");
}
// read file to check sudoku
void SetPuzzle(char filename[]){
    FILE *file = fopen(filename,"r");
    int i,j,ch,num;
    for (i=0;i<=9;i++){
        for(j=0;j<=9;j++){
            while(((ch = getc(file)) != EOF)){
                if(ch == EOF) break;
                if(ch == ',') break;
                if(ch == '\n') break;
                ungetc(ch,file);
                fscanf(file,"%d",&num);
                if(num!=-1)
                    puzzle[i][j] = num;            
            } 
        }
    }
    
    print_grid(puzzle);
    return;
}
int row_sum;
int col_sum;
//int sub_sum[9];
void* row_checker(void *data){
    if(rv==0)pthread_exit(NULL);
    int row_sum1=0;
    int row_sum2=0;
    int flag=0;
    for(int i=1;i<=9;i++){       
        if(flag==0){
            row_sum1=0;
            for(int j=1;j<=9;j++){
                row_sum1+=puzzle[i][j];
            }
            flag=1;

        }
        else if(flag==1){
            row_sum2=0;
            for(int j=1;j<=9;j++){
                row_sum2+=puzzle[i][j];
            }
            flag=0;

        }
        
        
        if(i==1){
                rv = 1;
            }
        else{
            if(row_sum2!=row_sum1){
                rv = 0;
                //printf("row,%d %d %d\n",i,row_sum1,row_sum2);
                pthread_exit(NULL);
                              
            }
            else {
                //printf("right,%d\n",i);
                rv = 1;
            }
        }
    }
    row_sum=row_sum1;
    pthread_exit(NULL);
}
void* col_checker(void *data){
    int col_sum1=0;
    int col_sum2=0;
    int flag=0;
    for(int i=1;i<=9;i++){ 
        if(rv==0)pthread_exit(NULL);      
        if(flag==0){
            col_sum1=0;
            for(int j=1;j<=9;j++){
                col_sum1+=puzzle[j][i];
            }
            flag=1;

        }
        else if(flag==1){
            col_sum2=0;
            for(int j=1;j<=9;j++){
                col_sum2+=puzzle[j][i];
            }
            flag=0;

        }
        
        
        if(i==1){
                rv = 1;
            }
        else{
            if(col_sum2!=col_sum1){
                rv = 0;
                //printf("col,%d %d %d\n",i,col_sum1,col_sum2);
                pthread_exit(NULL);
                              
            }
            else {
                //printf("right,%d\n",i);
                rv = 1;
            }
        }
    }
    //sleep(1);
    col_sum=col_sum1;
    pthread_exit(NULL);
}
void* sub_grid_checker(void* start){
    //sub_sum1=0;
    
    int k = atoi(start);
    //int i=k/10;
    //int j=k%10;
    int *sub_sum=malloc(sizeof(int));
    if(rv==0){
        pthread_exit((void*)sub_sum);
    }
    for(int i=k/10;i<=k/10+2;i++){
        for(int j=k%10;j<=k%10+2;j++){
            //printf("puzzle,%d\n",puzzle[i][j]);
            sub_sum[0]+=puzzle[i][j];

        }
    }   
    //sleep(1);
    //printf("grid,%d\n",sub_sum[0]);
    pthread_exit((void*)sub_sum);
}

int main(int argc, char* argv[])
{
	//int rv = 1; // flag to check answer
    // input the sudoku file
    rv = 1;

    SetPuzzle("test2.txt");
    pthread_t t1,t2;
    pthread_t t[9];
    void *sub_sum[9];
    int *sub_value[9];
    int value[9];
    pthread_create(&t1,NULL,row_checker,NULL);   
    pthread_create(&t2,NULL,col_checker,NULL);

    pthread_create(&t[0],NULL,sub_grid_checker,"11");
    pthread_create(&t[1],NULL,sub_grid_checker,"41");
    pthread_create(&t[2],NULL,sub_grid_checker,"71");
    pthread_create(&t[3],NULL,sub_grid_checker,"14");
    pthread_create(&t[4],NULL,sub_grid_checker,"44");
    pthread_create(&t[5],NULL,sub_grid_checker,"74");
    pthread_create(&t[6],NULL,sub_grid_checker,"17");
    pthread_create(&t[7],NULL,sub_grid_checker,"47");
    pthread_create(&t[8],NULL,sub_grid_checker,"77");
   


   
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    for(int i=0;i<9;i++){
        pthread_join(t[i],&sub_sum[i]);
        sub_value[i]=(int *)sub_sum[i];
        value[i]=sub_value[i][0]; 
        //printf("%d\n",sub_sum[i]);
        if(i!=0){
            if (value[i]!=value[i-1]){
                //printf("grid!!!\n");
                //printf("???%d %d\n",value[i],value[i-1]);
                rv=0;
                break;
            }
                
        }
        //printf("%d\n",value[i]);
    }

    if(col_sum!=row_sum || row_sum!=value[0] || col_sum!=value[0])rv=0;
    


   



    //printf("row sum %d\n",row_sum);
    //printf("col sum %d\n",col_sum);


    
    /*
     .
     .
     Your code here
     .
     .
     
    */
    
	if (rv == 1)
		printf("Successful :) \n");
	else
		printf("Must check again! :( \n");

	return 0;
}
