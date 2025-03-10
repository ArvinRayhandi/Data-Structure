#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 10

struct node
{
    char data[100];
    struct node *next;
} *hashTable[26], *curr;

int hashFunctionChoice = 0; // 0: First Character, 1: Division, 2: Folding

int collisionHandlingChoice = 0; // 0: Chaining, 1: Linear Probing, 2: Rehashing

int hashFunctionFirstChar(char data[])
{
    int hashKey = -1;
    char firstChar;

    // Ambil karakter pertama
    firstChar = data[0];
    hashKey = tolower(firstChar) - 97;
    return hashKey;
}

int divHash(int key)
{
    return key % TABLE_SIZE;
}

int foldingHash(int key)
{
    int part1 = key / 1000; // Ambil 4 digit pertama
    int part2 = key % 1000; // Ambil 4 digit terakhir

    return (part1 + part2) % TABLE_SIZE;
}

int midSquareHash(int key)
{
    long squared = key * key;
    int mid = (squared / 100) % 1000;
    return mid % TABLE_SIZE;
}

int digitExtractionHash(int key)
{
    int extractedDigits = (key / 1000) * 10 + (key % 10);
    return extractedDigits % TABLE_SIZE;
}

int rotationHash(int key)
{
    int lastDigit = key % 10;
    int rotatedKey = (key / 10) + (lastDigit * 1000);
    return rotatedKey % TABLE_SIZE;
}

int linearProbing(int hashKey, int attempt)
{
    return (hashKey + attempt) % TABLE_SIZE;
}

int rehashing(int hashKey, int attempt)
{
    return (hashKey + attempt * attempt) % TABLE_SIZE;
}

void pushBack(int hashKey, char data[])
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    strcpy(newNode->data, data);
    newNode->next = NULL;

    if (hashTable[hashKey] == NULL)
    {
        hashTable[hashKey] = newNode;
    }
    else
    {
        curr = hashTable[hashKey];
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = newNode;
    }
}

void viewHashTable()
{
    for (int i = 0; i < 26; i++)
    {
        if (hashTable[i] != NULL)
        {
            printf("Hash Table Index [%d] :\n", i);
            curr = hashTable[i];

            while (curr != NULL)
            {
                printf("%s ", curr->data);
                curr = curr->next;
            }
            printf("\n");
        }
    }
}

int main()
{
    char data[100];
    int key;

    printf("Pilih Hash Function:\n");
    printf("1. First Character\n");
    printf("2. Division\n");
    printf("3. Folding\n");
    printf("4. Mid-Square\n");
    printf("5. Digit Extraction\n");
    printf("6. Rotation\n");
    scanf("%d", &hashFunctionChoice);

    printf("Pilih Collision Handling:\n");
    printf("1. Chaining\n");
    printf("2. Linear Probing\n");
    printf("3. Rehashing\n");
    scanf("%d", &collisionHandlingChoice);

    do
    {
        printf("Input Data: ");
        scanf("%s", data);
        getchar();

        if (strcmpi(data, "exit") == 0)
            break;

        switch (hashFunctionChoice)
        {
        case 1:
            key = hashFunctionFirstChar(data);
            break;
        case 2:
            key = divHash(atoi(data));
            break;
        case 3:
            key = foldingHash(atoi(data));
            break;
        case 4:
            key = midSquareHash(atoi(data));
            break;
        case 5:
            key = digitExtractionHash(atoi(data));
            break;
        case 6:
            key = rotationHash(atoi(data));
            break;
        default:
            printf("Pilihan tidak valid.\n");
            return 1;
        }

        switch (collisionHandlingChoice)
        {
        case 1:
            pushBack(key, data);
            break;
        case 2:
            for (int attempt = 0; attempt < TABLE_SIZE; attempt++)
            {
                int newKey = linearProbing(key, attempt);
                if (hashTable[newKey] == NULL)
                {
                    pushBack(newKey, data);
                    break;
                }
            }
            break;
        case 3:
            for (int attempt = 0; attempt < TABLE_SIZE; attempt++)
            {
                int newKey = rehashing(key, attempt);
                if (hashTable[newKey] == NULL)
                {
                    pushBack(newKey, data);
                    break;
                }
            }
            break;
        default:
            printf("Pilihan tidak valid\n");
            return 1;
        }

    } while (true);

    viewHashTable();

    getchar();

    return 0;
}