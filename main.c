#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include <string.h>
#include<fcntl.h>
pthread_mutex_t lock; 
int main(){
pthread_mutex_init(&lock, NULL);
int i,n,p[10]={1,2,3,4,5,6,7,8,9,10},min,k=1,btime=0;
int bt[10],temp,j,at[10],wt[10],tt[10],ta=0,sum=0;
float wav=0,tav=0,tcal=0,wcal=0;
printf("Smallest one first \n");
printf("\n no. of processes :");
scanf("%d",&n);

for(i=0;i<n;i++){
printf("\nFor P%d\n",i+1);
pthread_mutex_lock(&plock);
	label:
       	 printf("Arrival time:");
        	 scanf("%d",&at[i]);
	if (at[i]==0){
		printf("\nArrival time should not be zero! Reenter! \n");
		goto label;
	}	
        bt[i]=at[i]*2;
        printf("Burst Time:%d\n",bt[i]);
	pthread_mutex_unlock(&plock);
}

for(i=0;i<n;i++){
	for(j=0;j<n;j++){
		if(at[i]<at[j]){
		temp=p[j];
			p[j]=p[i];
			p[i]=temp;
			temp=at[j];
			at[j]=at[i];
			at[i]=temp;
			temp=bt[j];
			bt[j]=bt[i];
			bt[i]=temp;
		}
	}
}



for(j=0;j<n;j++){
	btime=btime+bt[j];
	min=bt[k];
		for(i=k;i<n;i++){
			if (btime>=at[i] && bt[i]>min){
					temp=p[k];
					p[k]=p[i];
					p[i]=temp;
					temp=at[k];
					at[k]=at[i];
					at[i]=temp;
					temp=bt[k];
					bt[k]=bt[i];
					bt[i]=temp;
				}
			}
	k++;
}

wt[0]=0;
for(i=1;i<n;i++){
		wt[i]=0;
		for(int j=0;j<i;j++)
			wt[i]+=bt[j];
		wcal+=wt[i];
}

wav=( wcal /n);
	for(i=0;i<n;i++){
	ta=ta+bt[i];
	tt[i]=ta-at[i];
	tcal = tcal +tt[i];
	}

tav=( tcal /n);

printf("\n RESULT:-");
printf("\nProcess\t Burst\t Arrival\t Waiting\t Turn-around" );
for(i=0;i<n;i++){
	printf("\n p%d\t %d\t %d\t\t %d\t\t\t%d",p[i],bt[i],at[i],wt[i],tt[i]);
}

printf("\n\navg. waiting : %f",wav);
printf("\navg. turnaround : %f\n",tav);
return 0;
}
