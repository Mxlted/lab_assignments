#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char letter;
    struct node* next;
} node;

// Returns the number of nodes in the linked list.
int length(node* head)
{
    int count = 0;
    node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Parses the string in the linked list.
// If the linked list is head -> |a|->|b|->|c|,
// then toCString function will return "abc".
char* toCString(node* head)
{
    int len = length(head);
    char* str = (char*)malloc((len + 1) * sizeof(char)); // Allocate memory for the string
    int i = 0;
    node* current = head;
    while (current != NULL) {
        str[i] = current->letter; // Copy the letter to the string
        current = current->next;
        i++;
    }
    str[i] = '\0'; // Null-terminate the string
    return str;
}

// Inserts a character to the linked list.
// If the linked list is head -> |a|->|b|->|c|,
// then insertChar(&head, 'x') will update the linked list as follows:
// head -> |a|->|b|->|c|->|x|.
void insertChar(node** pHead, char c)
{
    node* newNode = (node*)malloc(sizeof(node)); // Create a new node
    newNode->letter = c;
    newNode->next = NULL;

    if (*pHead == NULL) {
        // If the list is empty, the new node becomes the head
        *pHead = newNode;
    } else {
        node* current = *pHead;
        while (current->next != NULL) {
            current = current->next;
        }
        // Add the new node at the end of the list
        current->next = newNode;
    }
}

// Deletes all nodes in the linked list.
void deleteList(node** pHead)
{
    node* current = *pHead;
    while (current != NULL) {
        node* next = current->next;
        free(current); // Free the memory of the current node
        current = next;
    }
    *pHead = NULL; // Set the head to NULL to indicate an empty list
}

int main(void)
{
    int i, strLen, numInputs;
    node* head = NULL;
    char* str;
    char c;
    FILE* inFile = fopen("input.txt", "r");

    fscanf(inFile, " %d\n", &numInputs);

    while (numInputs-- > 0)
    {
        fscanf(inFile, " %d\n", &strLen);
        for (i = 0; i < strLen; i++)
        {
            fscanf(inFile, " %c", &c);
            insertChar(&head, c);
        }

        str = toCString(head);
        printf("String is : %s\n", str);

        free(str);
        deleteList(&head);

        if (head != NULL)
        {
            printf("deleteList is not correct!");
            break;
        }
    }

    fclose(inFile);
}
