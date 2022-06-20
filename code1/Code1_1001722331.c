/* Coding Assignment 1 */
// Edward Alkire - 1001722331

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX 100

typedef struct node
{
	int number;
	struct node *next_ptr;
}
NODE;

void AddNodeToLL(int num_, NODE **llh_)
{
	NODE *temp, *NewNode;
	temp = *llh_; //llh is pointing to a pointer to the head node
	NewNode = malloc(sizeof(NODE));
	NewNode->number = num_;
	NewNode->next_ptr = NULL;

	//traverse to end of LL
	while(temp->next_ptr)
	{
		temp = temp->next_ptr;
	}
	//add new node to end of LL
	temp->next_ptr = NewNode;

}

void ReadFileIntoLL(int argc,  char *argv[], NODE **LLH, int *nodeCountPtr, int *sumPtr)
{
	char buf[MAX] = {};
	FILE *fp = NULL;
	fp = fopen(argv[1], "r");
	int num = 0;

	if(!fp)
	{
		printf("\nError opening file...exiting\n");
		return -1;
	}

	while((fgets(buf, sizeof(buf), fp)))
	{
		num = atoi(buf);
		AddNodeToLL(num, LLH);
		(*nodeCountPtr)++;
		(*sumPtr) += num;
	}
	fclose(fp);
}

void PrintLL(NODE *LLH)
{
	NODE *temp = LLH;
	while(temp)
	{
		printf("\n%d %d %d\n", temp, temp->number, temp->next_ptr);
		temp = temp->next_ptr;
	}
}

void FreeLL(NODE **LLH) 
{
	NODE *temp = *LLH;
	NODE *temp2 = temp;
	while(temp)
	{
		temp2 = temp;
		#ifdef PRINT
		printf("\nFreeing %d %d %d\n", temp2, temp2->number, temp2->next_ptr);
		#endif
		temp = temp->next_ptr;
		free(temp2);
	}
	*LLH = NULL;
}


/*
Create a program than can open a file listed on the command line,
read through that file, 
write each line from the file into a linked list, 
print the linked list
and free the linked list.
You will time each step and count and sum during each step.
*/

int main(int argc, char *argv[]) 
{
	NODE *LLH = NULL;
	int sum=0;
	int nCount=0;
	int *nodeCountPtr = &nCount;
	int *sumPtr = &sum;
	clock_t start, end;

	//^^use for getting sum and count later

	if(argc == 1)
	{
		printf("\nFile must be provided on command line...exiting\n");
		return -1;
	}
	
	/* capture the clock in a start time */
	start = clock();
	ReadFileIntoLL(argc, argv, &LLH, nodeCountPtr, sumPtr);
	/* capture the clock in an end time */
	end = clock();
	printf("\n%d records were read for a total sum of %d\n", nCount, sum);
	printf("\n%ld tics to write the file into the linked list\n", end-start);

	#ifdef PRINT
	/* capture the clock in a start time */
	start = clock();
	PrintLL(LLH);
	/* capture the clock in an end time */
	end = clock();
	printf("\n%d records were read for a total sum of %d\n", nCount, sum);
	printf("\n%ld tics to print the linked list\n", end-start);
	#endif
	
	
	/* capture the clock in a start time */
	start = clock();
	FreeLL(&LLH);
	/* capture the clock in an end time */
	end = clock();
	printf("\n%d nodes were deleted for a total sum of %d\n", nCount, sum);
	printf("\n%ld tics to free the linked list\n", end-start);
	
	free(nodeCountPtr);
	free(sumPtr);
	free(LLH);

	return 0; 
} 
