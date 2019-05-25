/*******************************************************************
 * Author:Matthew Solbrack
 * Date: 04/20/2019
 * Subject: HW 4. This Algorithm using the greedy method to find the  
 * combination of maximum activities to time. It is a Last to start
 * problem.
 * *****************************************************************/


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct activity
{
	int activityNumber;
	int startTime;
	int endTime;
}activity;

void mergeSort(int first, int last, struct activity * arr)
{
		//if n=1, done;
		if(last <= first)
			return;
		
		//Recursively sort
		int mid = (first + last)/2;
		mergeSort(first, mid, arr);
		mergeSort(mid+1, last, arr);

		//Merge the 2 sorted lists
		int placement;
		int left = first;
		int right = mid + 1;
		struct activity * temp;
		temp = malloc((last+1) * sizeof(struct activity));

		//place number into array as its being merged
		for (placement = first; placement <= last; placement++)
		{
			if(left == mid + 1)
			{
				temp[placement] = arr[right];
				right++;
			}
			else if(right == last + 1)
			{
				temp[placement] = arr[left];
				left++;
			}
			else if (arr[left].startTime > arr[right].startTime)
			{
				temp[placement] = arr[left];
				left++;
			}
			else 
			{
				temp[placement] = arr[right];
				right++;
			}

		}

		//Move number from the temp array to original array 
		for (placement = first; placement <= last; placement++)
		{
			arr[placement]=temp[placement];
		}

		free(temp);
}


int selectActivity(struct activity options[], int selected[], int numActivities)
{
	selected[0] = options[0].activityNumber;
	int time = options[0].startTime;
	int i = 1;
	int j = 1;
	while (time > 0 && i < numActivities)
	{
		if(time >= options[i].endTime)
		{
			selected[j] = options[i].activityNumber;
			time = options[i].startTime;
			j++;
		}		
	
		i++;

	}

	return j;
}



int main()
{
	struct activity options[100];
	int selected[50];
	int placement=0, numActivities, i=0, set=1;
	int * arr=malloc(500 * sizeof(int));
	FILE * textFile;	

	//Get the file information first
	if((textFile = fopen("act.txt", "r")))
	{
		while((fscanf(textFile, "%d", &arr[i])) != EOF)
		{
			i++;
		}
		fclose(textFile);
	}
	
	while (placement < i)
	{	
		int totalActivities=0;
		//Place the number activites into the placeholder
		numActivities = arr[placement];
	

		placement++;

		//Place the activity number, start time, and end time into it's specific struct
		for(int j=0; j < numActivities; j++)
		{
			options[j].activityNumber=arr[placement];
			placement++;
			options[j].startTime=arr[placement];
			placement++;
			options[j].endTime=arr[placement];
			placement++;
	
		}

		//Sort the struct's into last-to-first order of start time
		mergeSort(0, numActivities-1, options);

		totalActivities = selectActivity(options, selected, numActivities);

		printf("Set %d\nNumber of activies selected = %d\n", set, totalActivities);
		printf("Activies: ");
		for(int count=0; count < totalActivities; count++)
		{
			printf("%d ", selected[count]);
		}	

		printf("\n\n");

		set++;
	
	}

	free(arr);

	return 0;

}

	

