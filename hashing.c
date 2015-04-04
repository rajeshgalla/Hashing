#include "hashing.h"
#include<stdio.h>
#include<stdlib.h>

struct HashTable *CreateHashTable(int size)
{
	struct HashTable *h;
	h = (struct HashTable *) malloc ( sizeof(struct HashTable) );
	if(h == NULL)
	{
		printf("Memory Error");
		return NULL;
	}
	h->tsize = (int) size/LOAD_FACTOR;
	printf("h->tsize = %d",h->tsize);
	h->count = 0;
	//h->Table ;
	struct HashTableNode **temp =  malloc ( ( sizeof(struct HashTableNode *) ) * (h->tsize) );

	if( temp == NULL )
	{
		printf("Memory Error");
		return NULL;
	}
	int i;
	
	for( i=0 ; i < (h->tsize) ; i++)
        {
               temp[i]->next = NULL;
               temp[i]->bcount = 0;
        }	
	return h;
}

int HashSearch(struct HashTable *h,int data)
{
	struct ListNode *temp;
	
	int index = Hash(data,h->tsize);
	
	if(h->Table[index] == NULL)
		return 0;	

	temp = h->Table[index]->next;
	while(temp)
	{
		if(temp->data == data)
			return 1;
		temp = temp->next;
	}
	return 0;
}

int HashInsert(struct HashTable *h,int data)
{
	int index;
	struct ListNode *newNode;
	if(HashSearch(h,data))
		return 0;
	index = Hash(data,h->tsize);	
	newNode = (struct ListNode *) malloc (sizeof(struct ListNode));
	if(!newNode)
	{
		printf("Memory Error");
		return -1;
	}
	newNode->key = index;
	newNode->data = data;
	newNode->next = h->Table[index]->next;
	h->Table[index]->next = newNode;
	h->Table[index]->bcount++;
	h->count++;
	if(h->count/h->tsize > LOAD_FACTOR)
		Rehash(h);
	return 1;
}

int HashDelete(struct HashTable *h, int data)
{
	int index;
	struct ListNode *temp,*prev;
	index = Hash(data,h->tsize);
	for(temp = h->Table[index] -> next,prev = NULL; temp; prev = temp,temp = temp->next)
		if(temp->data == data)
		{
			if(prev != NULL)
				prev->next = temp->next;
			else
				h->Table[index]->next = temp->next;
		free(temp);
		h->Table[index]->bcount--;
		h->count--;
		return 1;
		}
	return 0;
}

void Rehash(struct HashTable *h)
{
	int oldsize,i,index;
	struct ListNode *p,*temp,*temp2;
	struct HashTableNode **oldTable;
	oldsize = h->tsize;
	oldTable = h->Table;
	h->tsize *= 2;
	h->Table = (struct HashTableNode **) malloc (sizeof(struct HashTableNode) * h->tsize);
	if(h->Table)
	{
		printf("Memory Error");
		return;
	}
	
	for(i=0;i<oldsize;i++)
	{
		for(temp = oldTable[i]->next;temp;temp = temp->next)
		{
			index = Hash(temp->data,h->tsize);
			temp2 = temp;
			temp = temp->next;
			temp2->next = h->Table[index]->next;
			h->Table[index]->next = temp2;
		}				

	}
}

int Hash(int data, int size)
{
	return data % size;
}
