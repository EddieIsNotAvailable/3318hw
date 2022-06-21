/* Coding Assignment 1 */
// Edward Alkire - 1001722331
// Linked list implementation

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX 1024

typedef struct node
{
	int number;
	struct node *next_ptr;
}
NODE;

void AddNodeToLL(int num_, NODE **llh_)
{
	NODE *temp = NULL;
    NODE *NewNode = NULL;
    temp = *llh_;
    NewNode = (NODE *)malloc(sizeof(NODE));
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
		exit(1);
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
	NODE *temp = LLH->next_ptr;
	while(temp)
	{
		printf("\n%p %d %p\n", temp, temp->number, temp->next_ptr);
		temp = temp->next_ptr;
	}
}

void FreeLL(NODE **LLH) 
{
	NODE *temp = *LLH;
    temp = temp->next_ptr;
	NODE *temp2 = temp;
	while(temp)
	{
		temp2 = temp;
		#ifdef PRINT
		printf("\nFreeing %p %d %p\n", temp2, temp2->number, temp2->next_ptr);
		#endif
		temp = temp->next_ptr;
		free(temp2);
	}
	*LLH = NULL;
}

int main(int argc, char *argv[]) 
{
	NODE *LLH = NULL;
    LLH = (NODE *)malloc(sizeof(NODE));
    LLH->number = 0;
    LLH->next_ptr = NULL;

	int sum=0;
	int nCount=0;
	int *nodeCountPtr = &nCount;
	int *sumPtr = &sum;
	clock_t start, end;


	if(argc == 1)
	{
		printf("\nFile must be provided on command line...exiting\n");
		return -1;
	}
	
	start = clock();
	ReadFileIntoLL(argc, argv, &LLH, nodeCountPtr, sumPtr);
	end = clock();
	printf("\n%d records were read for a total sum of %d\n", nCount, sum);
	printf("\n%ld tics to write the file into the linked list\n", end-start);

	#ifdef PRINT
	start = clock();
	PrintLL(LLH);
	end = clock();
	printf("\n%d records were read for a total sum of %d\n", nCount, sum);
	printf("\n%ld tics to print the linked list\n", end-start);
	#endif
	
	start = clock();
	FreeLL(&LLH);
	end = clock();
	printf("\n%d nodes were deleted for a total sum of %d\n", nCount, sum);
	printf("\n%ld tics to free the linked list\n", end-start);
	
	nodeCountPtr=NULL;
	sumPtr=NULL;

	return 0; 
}