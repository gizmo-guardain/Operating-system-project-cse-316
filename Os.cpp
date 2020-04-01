#include<stdio.h> 

void rr(int no,int remt[10],int Cur_t,int arT[10], int bsT[10]);

int main() 
{
	int processNo,currentTime,remainingProcess,indicator=0,wait=0,turnAroundTime=0,arrivalTime[10],burstTime[10],remainingTime[10],x=1;
	printf("Number of processes ");
	int n;
	scanf("%d",&n);
	remainingProcess = n;
	printf("\nEnter the arrival time and burst time of the processes\n");
	for(processNo = 0;processNo < n;processNo++) 
	{
		printf("\nProcess P%d\n",processNo+1);
		printf("Arrival time = "); 
		scanf("%d",&arrivalTime[processNo]);
		printf("Burst time = "); 
		scanf("%d",&burstTime[processNo]); 
		remainingTime[processNo]=burstTime[processNo]; 
	} 
	printf("Time quantum for first round is 6.\n");
	int timeQuantum=6;
	currentTime=0;
	for(processNo=0;remainingProcess!=0;) 
	{
		if(remainingTime[processNo]<=timeQuantum && remainingTime[processNo]>0)
		{ 
			currentTime+=remainingTime[processNo]; 
			remainingTime[processNo]=0; 
			indicator=1; 
		} 
		else if(remainingTime[processNo]>0)
		{ 
			remainingTime[processNo]-=timeQuantum; 
			currentTime+=timeQuantum; 
		} 
		if(remainingTime[processNo]==0 && indicator==1)			
		{ printf("%d",processNo);
			remainingProcess--;				
			printf("P %d",processNo+1); 
			printf("\t\t\t%d",currentTime-arrivalTime[processNo]);
			printf("\t\t\t%d\n",currentTime-burstTime[processNo]-arrivalTime[processNo]);
			wait+=currentTime-arrivalTime[processNo]-burstTime[processNo]; 
			turnAroundTime+=currentTime-arrivalTime[processNo]; 
			indicator=0; 
		} 
		if(processNo==n-1){
			x++;
			if(x==2){
				processNo=0;
				timeQuantum=6;
				
				printf("Time quantum for second round is 10. \n");
			}
			else{
				break;
			}
		}
		else if(currentTime >= arrivalTime[processNo+1]){
			processNo++;
		}
		else{
			processNo=0;
		}
	}
	
	rr(n,remainingTime,currentTime,arrivalTime,burstTime);
	
	return 0;
}

void rr(int no,int remainingTime[10],int currenttime,int arrivalTime[10], int burstTime[10]){	
	float avg_wait,avg_tut;
    int i,j,n=no,temp,btime[20],Proc_no[20],w_time[20],tut_t[20],total=0,loc;
    
    printf("Third round with more burst time.\n");
    
    for(i=0;i<n;i++)
    {
        btime[i]=remainingTime[i];
        w_time[i]=currenttime-arrivalTime[i]-btime[i];
		Proc_no[i]=i+1;
    }
	
    for(i=0;i<n;i++)
    {
        loc=i;
        for(j=i+1;j<n;j++)
        {
            if(btime[j]<btime[loc]){
            	loc=j;
            }
        }
        temp=btime[i];
        btime[i]=btime[loc];
        btime[loc]=temp;
        temp=Proc_no[i];
        Proc_no[i]=Proc_no[loc];
        Proc_no[loc]=temp;
    }
	
    for(i=1;i<n;i++)
    {
        for(j=0;j<i;j++){
        	w_time[i]+=btime[j];
        }
        total+=w_time[i];
    }
    avg_wait=(float)total/n;
    total=0;
    printf("\nProcess\t\tBurst time\t\twaiting time\t\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        tut_t[i]=btime[i]+w_time[i];
        total=total + tut_t[i];
        printf("\nP%d\t\t\t%d\t\t\t%d\t\t\t%d",Proc_no[i],btime[i],w_time[i],tut_t[i]);
    }
    avg_tut=(float)total/n;
    printf("\n\nAverage waiting time = %f",avg_wait);
    printf("\n Average turnaround time = %f\n",avg_tut);
	
}
