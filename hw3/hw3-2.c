#include <stdio.h>
#include<stdlib.h>

double ans(float number)
{
	int k =0;
	k = 1000000*number;
	//printf("%d\n",k );
	if(k%10>4){
		k+=10;
	}
	k=k/10;
	float ans;
	ans=(float)k/100000;
	return ans;
}

int main(int argc, char const *argv[])
{
	int n;
	FILE *fp;
	fp = fopen(argv[1], "r");
	fscanf(fp,"%d",&n);
	int P[n][2];
	int flag[n];
	int rs[n];
	int w_time[n];
	int t_time[n];
	int work_time[n];
	for(int i = 0; i < n; i++){
		fscanf(fp,"%d",&P[i][0]);
		
		flag[i]=0;
		w_time[i]=0;
		t_time[i]=0;
		work_time[i]=0;
		rs[i]=0;	
	}
	for(int i = 0; i < n; i++){
		fscanf(fp,"%d",&P[i][1]);
		
	}
	fclose(fp);
	int time = 0;
	//int busy=0;
	//int qq[n]={'\0'};
	//int q1_v=101;
	int Q;
	//int q1;
	while(1){
		int q1;
		int q1_v=101;
		//printf("time %d\n",time );

		for(int i = 0; i < n; i++){
			if(time == P[i][0]){
				flag[i]=1;	
				//printf("i %d\n",i);
			}
			if(flag[i]==1){
				if(P[i][1]<q1_v){
					
						q1 = i;
						q1_v=P[i][1];
						//printf("q1 %d\n",q1 );
				}

			}
		}
		for(int i=0;i<n;i++){
			
			if(i!=q1)rs[i]=1;
			if(work_time[i]==0)rs[i]=0;
		}

		
		if(flag[q1] == 1){
			
			Q = q1;
			if(work_time[Q] ==0&&rs[Q]==0){
				w_time[Q]=time-P[Q][0];
				//printf("%dwaiting %d\n",Q,w_time[Q] );
				

			}
			else if(work_time[Q]>0&&rs[Q]==1){
				rs[Q]=0;
				w_time[Q]=w_time[Q]+(time-work_time[Q]);
				//printf("%dwaiting %d\n",Q,w_time[Q] );
			}
			work_time[Q]=time+1;		
			P[Q][1]=P[Q][1]-1;

			if(P[Q][1]==0){
				//printf("Q %d finish\n", Q);
				t_time[Q]= time-P[Q][0]+1;
				flag[Q] = 0;
				
				
			}

		}
		
		time++;
		int num=n;
			for(int j=0;j<n;j++){
				if(P[j][1]==0)num--;

			}
			if(num==0){
				//printf("time %d\n",time );
				break;
			}	
	}
	FILE *fp2;
	fp2=fopen("ans2.txt", "w");
	float a_w=0;
	float a_t=0;

	
	for(int i = 0; i < n; i++){
		fprintf(fp2,"%d %d\n",w_time[i],t_time[i]);
		a_w+=w_time[i];
		a_t+=t_time[i];
		
	}
	a_w=ans((float)a_w/(float)n);
	a_t=ans((float)a_t/(float)n);
	
	
	if(a_w>=100)fprintf(fp2,"%.8g\n",a_w );
	else fprintf(fp2,"%.7g\n",a_w );
	if(a_t>=100) fprintf(fp2,"%.8g\n",a_t );
	else fprintf(fp2,"%.7g\n",a_t );
	fclose(fp2);

	return 0;
}