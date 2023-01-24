#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Process
{
	int pid;
	int BT;
	int AT;
	int WT;
	int TAT;
	bool isSelected;
};

void swap(struct Process *xp, struct Process *yp) 
{ 
    struct Process temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
}

void sortedProcess(struct Process p[],int n)
{
	int i,j,min_index;
	for (i = 0; i < n-1; ++i)
	{
		min_index = i;
		for (j = i+1; j < n; ++j)
		{
			if(p[j].BT < p[min_index].BT)
			{
				min_index = j;
			}
		}
		if (p[min_index].AT != p[i].AT)
		{
			swap(&p[min_index],&p[i]);
		}
	}
}

void sort(struct Process p[],int n)
{
	int i,j,min_index;
	for (i = 0; i < n-1; ++i)
	{
		if(p[i].AT == p[i+1].AT && p[i].BT > p[i+1].BT)
		{
            swap(&p[i+1],&p[i]);
		}
		
	}
}

int selectProcess(struct Process p[],int n,int time)
{
	for (int i = 0; i < n; ++i)
	{
		if(p[i].AT<=time && !p[i].isSelected)
			return i;
	}
	return -1;
}

void calculate_tat(struct Process p[],int n)
{
	 int time = 0;
	 float avg_tat=0;
	 float avg_wt = 0;
	 
     for (int i = 0; i < n; ++i)
     {
     	 int index = selectProcess(p,n,time);
     	 while(index <0)
     	 {
     		time++;
     		index = selectProcess(p,n,time);
     	 }
		 p[index].isSelected = true;
		 time += p[index].BT;
		 p[index].TAT = time - p[index].AT;
		 p[index].WT = p[index].TAT - p[index].BT;
		 avg_wt += p[index].WT;
		 avg_tat += p[index].TAT;
	 	
	 	 printf("%d\t%d\t%d\t%d\t%d\n",p[index].pid+1,p[index].AT,p[index].BT,p[index].TAT,p[index].WT);
     }
     avg_tat /= n;
     avg_wt /= n;
     printf("\nAverage TAT %f\n",avg_tat);
     printf("Average WT %f\n",avg_wt);
}

int main()
{
	int n,i;
	printf("Enter the number of Process\n");
	scanf("%d",&n);
	struct Process process[n];
	printf("\nEnter the details of Process Burst Time and Arrival Time \n");
	for (i = 0; i < n; ++i)
	{
		scanf("%d%d",&process[i].BT,&process[i].AT);
		process[i].pid = i;
		process[i].isSelected = false;
	}
	printf("\nProcess\tAT\tBT\tTAT\tWT\n");
	sortedProcess(process,n);
	calculate_tat(process,n);
	return 0;
}