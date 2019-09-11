#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

#define NUMBER_OF_THREADS 11 /* Hint */
#define PUZZLE_SIZE 9

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
int main(int argc, char* argv[])
{
	int rv = 1; // flag to check answer
    // input the sudoku file
    SetPuzzle("test2.txt");
    //check row
    int row_sum1=0;
    int row_sum2=0;
    int flag1=0;
    for(int i=1;i<=9;i++){
        
        if(flag1==0){
            row_sum1=0;
            for(int j=1;j<=9;j++){
                row_sum1+=puzzle[i][j];
            }
            flag1=1;

        }
        else if(flag1==1){
            row_sum2=0;
            for(int j=1;j<=9;j++){
                row_sum2+=puzzle[i][j];
            }
            flag1=0;

        }
        

        if(i==1){
                rv = 1;
            }
        else{
            if(row_sum2!=row_sum1){
                rv = 0;
                //printf("row,%d %d %d\n",i,row_sum1,row_sum2);
                //printf("Must check again! :( \n");
                //return 0;
                
            }
            else rv = 1;
        }
    }
    //sleep(1);
    int col_sum1=0;
    int col_sum2=0;
    int flag2=0;
    for(int i=1;i<=9;i++){
        if(rv==0)break;
        
        if(flag2==0){
            col_sum1=0;
            for(int j=1;j<=9;j++){
                col_sum1+=puzzle[i][j];
            }
            flag2=1;

        }
        else if(flag2==1){
            col_sum2=0;
            for(int j=1;j<=9;j++){
                col_sum2+=puzzle[i][j];
            }
            flag2=0;

        }
        

        if(i==1){
                rv = 1;
            }
        else{
            if(col_sum2!=col_sum1){
                rv = 0;
                //printf("col,%d %d %d\n",i,col_sum1,col_sum2);
                //printf("Must check again! :( \n");
                //return 0;
                
            }
            else rv = 1;
        }
    }
    //sleep(1);
    if(row_sum1!=col_sum1){

        rv=0;
        //printf("r+c\n");
        //printf("Must check again! :( \n");

    }
    int sub_sum[9]={0};

    
        
    for(int k=1;k<=9;k+=3){
        if(rv==0)break;
        for(int i=k;i<=k+2;i++){
            for(int j=1;j<=3;j++){
                sub_sum[k-1]+=puzzle[i][j];
                

                }
        }
        //printf("%d %d\n",sub_sum[k-1],k);
    }

    
    
        
    for(int k=1;k<=9;k+=3){
        if(rv==0)break;
        for(int i=k;i<=k+2;i++){
            for(int j=4;j<=6;j++){
                sub_sum[k]+=puzzle[i][j];
                //printf("%d %d %d\n",sub_sum[k]);

                }
        }
        //printf("%d %d\n",sub_sum[k],k);
    }

    
    
        
    for(int k=1;k<=9;k+=3){
        if(rv==0)break;
        for(int i=k;i<=k+2;i++){
            for(int j=7;j<=9;j++){
                sub_sum[k+1]+=puzzle[i][j];
                
            }
        }
        //printf("%d\n",sub_sum[k+1] );

    }
    for(int i=0;i<9;i++){
        if(i==0) rv=rv;
        else if(sub_sum[i]!=sub_sum[i-1]){
           // printf("here\n");
            rv=0;

        }
    }
        
    

    if(sub_sum[0]!=col_sum1){
        //printf("s+c\n");
       // printf("%d\n",sub_sum[0]);
        

        rv=0;

    }
    //sleep(1);

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
