#define LOAD_FACTOR 20
#define INITIAL_SIZE 200

struct HashTable *CreateHashTable(int size);
int HashSearch(struct HashTable *h,int data);
int HashInsert(struct HashTable *h,int data);
int HashDelete(struct HashTable *h, int data);
void Rehash(struct HashTable *h);
int Hash(int data, int size);


struct ListNode 
{
	int key;
	int data;
	struct ListNode *next;	
};

struct HashTableNode 
{
	int bcount;
	struct ListNode *next;
};

struct HashTable
{
	int tsize;
	int count;
	struct HashTableNode **Table;
};
