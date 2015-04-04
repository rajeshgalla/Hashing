#include<stdio.h>
#include "hashing.h"

int main(void)
{
	struct HashTable *h;
	h = CreateHashTable(INITIAL_SIZE);
	
	int input;
	
	printf("Enter input integers and -1 to end : ");
	scanf("%d",&input);	
	
	while(input != -1 )
	{
		if(HashInsert(h,input) == 1)
		{
			printf("Inserted successfully");
		}
		else
			printf("Insert failed");
		scanf("%d",&input);	
	}
	
	return 0;
}
