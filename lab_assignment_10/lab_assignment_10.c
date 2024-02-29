#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node structure
struct TrieNode
{
    int count;
    struct TrieNode* children[26]; // for lowercase letters 'a' to 'z'
};

// Initializes a trie node
struct TrieNode* createTrieNode()
{
    struct TrieNode* pNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    pNode->count = 0;
    for (int i = 0; i < 26; i++)
    {
        pNode->children[i] = NULL;
    }
    return pNode;
}

// Trie structure
struct Trie
{
	struct TrieNode* root;
};

// Initializes a trie structure
struct Trie* createTrie()
{
    struct Trie* pTrie = (struct Trie*)malloc(sizeof(struct Trie));
    pTrie->root = createTrieNode();
    return pTrie;
}

// Inserts the word to the trie structure
void insert(struct Trie* pTrie, char* word)
{
    struct TrieNode* pNode = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        char c = word[i];
        if (c < 'a' || c > 'z') {
            // Skip non-lowercase alphabet characters
            continue;
        }

        int index = c - 'a';
        if (pNode->children[index] == NULL)
        {
            pNode->children[index] = createTrieNode();
        }
        pNode = pNode->children[index];
    }
    pNode->count++;
}

// computes the number of occurances of the word
int numberOfOccurrences(struct Trie* pTrie, char* word)
{
    struct TrieNode* pNode = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';
        if (pNode->children[index] == NULL)
        {
            return 0;
        }
        pNode = pNode->children[index];
    }
    return pNode->count;
}

// Deallocates the trie node
void deallocateTrieNode(struct TrieNode* pNode)
{
    if (pNode == NULL)
    {
        return;
    }
    for (int i = 0; i < 26; i++)
    {
        deallocateTrieNode(pNode->children[i]);
    }
    free(pNode);
}

// deallocate the trie structure
struct Trie* deallocateTrie(struct Trie* pTrie)
{
    deallocateTrieNode(pTrie->root);
    free(pTrie);
    return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char* filename, char** pInWords)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return 0;
    }

    int numWords = 0;
    char word[256];

    while (fscanf(file, "%s", word) != EOF)
    {
        pInWords[numWords] = (char*)malloc(strlen(word) + 1);
        strcpy(pInWords[numWords], word);
        numWords++;
    }

    fclose(file);
    return numWords;
}

int main(void)
{
    char* inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct Trie* pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }

    // Parse line by line, and insert each word to the trie data structure
    char* pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }

    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
    {
        printf("There is an error in this program\n");
    }

    // Free dynamically allocated words from the dictionary
    for (int i = 0; i < numWords; i++)
    {
        free(inWords[i]);
    }

    return 0;
}
