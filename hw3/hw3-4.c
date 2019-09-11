#include<stdio.h>
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
	//int working[n];
	int w1[n],w2[n];
	for(int i = 0; i < n; i++){
		fscanf(fp,"%d",&P[i][0]);
		flag[i]=0;
		w_time[i]=0;
		t_time[i]=0;
		rs[i]=0;
		work_time[i]=P[i][0];
		w1[i]=0;
		w2[i]=0;
	}
	for(int i = 0; i < n; i++){
		fscanf(fp,"%d",&P[i][1]);
		
	}
	int time_q1,time_q2;
	fscanf(fp,"%d",&time_q1);
	fscanf(fp,"%d",&time_q2);
	fclose(fp);
	int time=0;
	int level=0;
	int counter1 = time_q1;
	int counter2 = time_q2;
	int busy=0,busy2=0,busy3=0;
	int q1;
	int Q;
	while(time<100){
		printf("time %d\n",time);
		int level=0;
		for(int i = 0; i < n; i++){
			if(time == P[i][0]){
				flag[i]=1;
				w1[i]=1;

			}
		}
		for(int i =0;i<n;i++){
			if(flag[i]==1){
				level=1;
				break;
				
			}
			
		}
		if(level!=1){
			for(int i =0;i<n;i++){
			if(flag[i]==2){
				level=2;
				break;
				
				}
			
			}

		}
		if(level!=2){
			for(int i =0;i<n;i++){
			if(flag[i]==3){
				level=3;
				break;
				
				}
			
			}
		}
		printf("level%d\n",level);
		/*Queue 1*/
		if(level==1){
			if(busy==0){
				busy=1;
				for(int i=0;i<n;i++){
					if(flag[i]==1){
						q1=i;
						break;
					}
				}
				for(int i =0; i<n; i++){
					if(flag[i]==1&&q1!=i){
						w1[i]++;

					}
					else w1[i]=0;

				}			
				if(rs[q1]==0){
					w_time[q1]=w_time[q1]+time-work_time[q1];
					rs[q1]=1;
					//printf("p%d waiting in q1 %d\n",q1+1,w_time[q1] );
				}
				P[q1][1]=P[q1][1]-1;
				work_time[q1]=time+1;
				if(P[q1][1]==0){
					counter1=time_q1;
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
					counter1=counter1-1;
					
				}
				if(counter1==0){
					counter1=time_q1;
					flag[q1]=2;
					rs[q1]=0;
					w2[q1]=1;
				}

			}

			else{
				if(counter1 == time_q1&&P[q1][1]!=0){
					int qq=0;
					for(int i=0;i<n;i++){
						if(flag[i]==1){
							if(w1[i]>qq){
								q1=i;
								qq=w1[i];
							}	
						}
					}
					

				}
				else if(counter1>0&&counter1<time_q1){
					q1=q1;

				}			
				for(int i=0;i<n;i++){
						if(flag[i]==1&&q1!=i){
						w1[i]++;
						}
						else w1[i]=0;
				}
				if(rs[q1]==0){
					w_time[q1]=w_time[q1]+(time-work_time[q1]);
					rs[q1]=1;
					//printf("p%d waiting in q1 %d\n",q1+1,w_time[q1] );
				}
				P[q1][1]=P[q1][1]-1;
				work_time[q1]=time+1;
				if(P[q1][1]==0){
					counter1=time_q1;
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
					counter1=counter1-1;
				}
				if(counter1==0&&P[q1][1]!=0){
					counter1=time_q1;
					flag[q1]=2;
					rs[q1]=0;
					w2[q1]=1;
				}


			}
			for(int i =0;i<n;i++){
				if(flag[i]==2){
					w2[i]++;
				
				}
			}


		}
		
		
		/*Queue2*/
		else if(level==2){
			printf("busy2 %d\n",busy2 );
			if(busy2==0){
				busy2=1;
				for(int i=0;i<n;i++){
					if(flag[i]==2){
						q1=i;
						break;
					}
				}
			for(int i =0; i<n; i++){
				if(flag[i]==2&&q1!=i){
					w2[i]++;
				}
				else w2[i]=0;

			}			
			if(rs[q1]==0){
				w_time[q1]=w_time[q1]+time-work_time[q1];
				rs[q1]=1;
				//printf("p%d waiting in q2 %d\n",q1+1,w_time[q1] );
			}
			P[q1][1]=P[q1][1]-1;
			work_time[q1]=time+1;
			if(P[q1][1]==0){
				counter2=time_q2;
				flag[q1]=0;
				t_time[q1]=time-P[q1][0]+1;
				busy2=0;
				for(int i =0; i<n ;i++){
					if(flag[i]==2){
						busy2=1;
					}

				}

			}
			else{
				counter2=counter2-1;
				
			}
			if(counter2==0&&P[q1][1]!=0){
				counter2=time_q2;
				flag[q1]=3;
				rs[q1]=0;
			}

		}

			else{
				if(counter2 == time_q2){
					int qq=0;
					for(int i=0;i<n;i++){
						if(flag[i]==2){
							if(w2[i]>qq){
								q1=i;
								qq=w2[i];
							}	
						}
					}
					

				}
				else if(counter2>0&&counter2<time_q2){
					q1=q1;

				}			
				for(int i=0;i<n;i++){
						if(flag[i]==2&&q1!=i){
						w2[i]++;
						}
						else w2[i]=0;
				}
				if(rs[q1]==0){
					w_time[q1]=w_time[q1]+(time-work_time[q1]);
					rs[q1]=1;
					//printf("p%d waiting in q2 %d\n",q1+1,w_time[q1] );
				}
				P[q1][1]=P[q1][1]-1;
				work_time[q1]=time+1;
				if(P[q1][1]==0){
					counter2=time_q2;
					flag[q1]=0;
					//q1=0;
					t_time[q1]=time-P[q1][0]+1;
					busy2=0;
					for(int i =0; i<n ;i++){
						if(flag[i]==2){
							busy2=1;
						}

					}
				}
				else{
					counter2=counter2-1;
				}
				if(counter2==0&&P[q1][1]!=0){//
					counter2=time_q2;
					flag[q1]=3;
					rs[q1]=0;
				}


			}	

		}

		/* * * * * * */
		
		/*Queue3*/
		else {
			int q3;
			int q3_v=101;
			for(int i = 0; i < n; i++){		
				
				if(flag[i]==3){
					if(P[i][1]<q3_v){				
						q3 = i;
						q3_v=P[i][1];
						
					}
				}
			}
			if(busy3 == 0 && flag[q3] == 3){
			busy3=1;
			Q = q3;
			w_time[Q]=time-work_time[Q]+w_time[Q];
			//printf("w_time %d \n",w_time[Q]);
			flag[Q] = 0;
			P[Q][1]=P[Q][1]-1;
			if(P[Q][1]==0){
				t_time[Q]= time-P[Q][0]+1;;
				
				busy3 = 0;
			}

			}
			else if(busy3==1){
				P[Q][1]=P[Q][1]-1;
				printf("time %d %d\n",time,P[Q][1] );
				if(P[Q][1]==0){
					t_time[Q]= time-P[Q][0]+1;
					printf("hi\n");
					//printf("time %d %d\n",time,P[Q][0] );
					busy3 = 0;
					flag[Q]=0;
				}

			}
		}
		

		time++;
		int num=n;


		for(int j=0;j<n;j++){
			printf("p%d %d\n",j,P[j][1] );
			printf("flag%d state %d\n",j,flag[j] );
			if(P[j][1]==0){
				//printf("j %d\n",j);
				num--;
			}
		}

		
		if(num==0){
			//printf("time %d\n",time );
			break;
		}
	}

	
	FILE *fp2;
	fp2=fopen("ans4.txt", "w");
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