#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
};

// Node for separate chaining
struct Node
{
    struct RecordType record;
    struct Node* next;
};

// Fill out this structure
struct HashType
{
    struct Node** table; // Pointer to an array of pointers to nodes
    int size;            // Size of the hash table (number of buckets)
};

// Compute the hash function
int hash(int x, int size)
{
    return x % size; // Simple modulo hashing for even distribution
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    int i;
    for (i = 0; i < hashSz; ++i)
    {
        printf("index %d -> ", i);
        struct Node* current = pHashArray->table[i];
        while (current != NULL)
        {
            printf("%d %c %d -> ", current->record.id, current->record.name, current->record.order);
            current = current->next;
        }
        printf("\n");
    }
}

int main(void)
{
    struct RecordType* pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Your hash implementation
    int hashSize = 10; // Choose an appropriate size for your hash table
    struct HashType hashTable;
    hashTable.size = hashSize;
    hashTable.table = (struct Node**)malloc(sizeof(struct Node*) * hashSize);
    
    // Initialize the hash table with NULLs (empty buckets)
    for (int i = 0; i < hashSize; ++i)
        hashTable.table[i] = NULL;

    // Insert records into the hash table using separate chaining
    for (int i = 0; i < recordSz; ++i)
    {
        int index = hash(pRecords[i].id, hashSize);
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->record = pRecords[i];
        newNode->next = hashTable.table[index];
        hashTable.table[index] = newNode;
    }

    // Display the records stored in the hash table
    displayRecordsInHash(&hashTable, hashSize);

    // Free memory
    for (int i = 0; i < hashSize; ++i)
    {
        struct Node* current = hashTable.table[i];
        while (current != NULL)
        {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable.table);
    free(pRecords);

    return 0;
}
