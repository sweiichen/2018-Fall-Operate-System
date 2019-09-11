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
	int w_time[n];
	int t_time[n];
	int work_time[n];
	int rs[n];
	int q[n];
	for(int i = 0; i < n; i++){
		fscanf(fp,"%d",&P[i][0]);
		flag[i]=0;
		w_time[i]=0;
		t_time[i]=0;
		rs[i]=0;
		work_time[i]=P[i][0];
		q[i]=0;	
	}
	for(int i = 0; i < n; i++){
		fscanf(fp,"%d",&P[i][1]);
		
	}
	int time_q;
	fscanf(fp,"%d",&time_q);
	fclose(fp);

	int time=0;
	int busy=0;
	int counter;
	counter=time_q;
	int q1;
	for(int i=0;i<n;i++){
		printf("p%d %d\n",i,P[i][0]);
	}
	
	while(1){
		//printf("time %d\n",time );

		for(int i = 0; i < n; i++){
			if(time == P[i][0]){
				flag[i]=1;
				q[i]=1;

			}
		}
		for(int i=0;i<n;i++){
			printf("flag%d %d\n",i,flag[i]);
		}
		printf("busy%d\n", busy);

		

		if(busy==0){
			busy=1;
			for(int i=0;i<n;i++){
				if(flag[i]==1){
					printf("flag[%d]is true\n",i);
					q1=i;
					printf("q1 %d\n",q1);
				break;
				}
				
			}
			for(int i =0; i<n; i++){
				if(flag[i]==1&&q1!=i){
					q[i]++;
				}
				else q[i]=0;

			}			
			if(rs[q1]==0){
				w_time[q1]=w_time[q1]+time-work_time[q1];
				rs[q1]=1;
				//printf("p%d waiting zz %d\n",q1+1,w_time[q1] );
			}
			P[q1][1]=P[q1][1]-1;
			work_time[q1]=time+1;
			if(P[q1][1]==0){
				counter=time_q;
				flag[q1]=0;
				t_time[q1]=time-P[q1][0]+1;
				busy=0;
				for(int i =0; i<n ;i++){
					if(flag[i]==1){
						busy=1;
					}

				}

			}
			else{
				counter=counter-1;
				
			}
			if(counter==0){
				counter=time_q;
				rs[q1]=0;
			}

		}

		else{
			if(counter == time_q){
				int qq=0;
				for(int i=0;i<n;i++){
					if(flag[i]==1){
						if(q[i]>qq){
							q1=i;
							qq=q[i];
						}	
					}
				}
				

			}
			else if(counter>0&&counter<time_q){
				q1=q1;

			}			
			for(int i=0;i<n;i++){
					if(flag[i]==1&&q1!=i){
					q[i]++;
					}
					else q[i]=0;
			}
			if(rs[q1]==0){
				w_time[q1]=w_time[q1]+(time-work_time[q1]);
				rs[q1]=1;
				//printf("p%d waiting %d\n",q1+1,w_time[q1] );
			}
			P[q1][1]=P[q1][1]-1;
			work_time[q1]=time+1;
			if(P[q1][1]==0){
				counter=time_q;
				flag[q1]=0;
				//q1=0;
				t_time[q1]=time-P[q1][0]+1;
				busy=0;
				for(int i =0; i<n ;i++){
					if(flag[i]==1){
						busy=1;
					}

				}
			}
			else{
				counter=counter-1;
			}
			if(counter==0){
				counter=time_q;
				rs[q1]=0;
			}


		}	

		time++;
		printf("%d time %d\n",q1,time );
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
	fp2=fopen("ans3.txt", "w");
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