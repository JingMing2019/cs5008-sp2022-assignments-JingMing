// name: Jing Ming
// email: ming.j@northeastern.edu
// Hash table using doubly linked list for chaning/

#include <stdio.h>
#include <stdlib.h>

struct bucket* hashTable = NULL;
int BUCKET_SIZE = 10;

// node struct
struct node {
    // Add your code here
    int key;
    int value;
    struct node* prev;
    struct node* next;
};

// bucket struct
struct bucket{
    // Add your code here
    struct node* head;
    int count;
};

// create a new node
struct node* createNode(int key, int value){

    // Add your code here
    struct node* newNode = (struct node*)malloc(sizeof(struct node)); // Attention: sizeof struct not struct pointer
    if (newNode != NULL) {
	   newNode -> key = key;
	   newNode -> value = value;
	   newNode -> prev = NULL;
	   newNode -> next = NULL;
    }

    return newNode;
}

void freeNode(struct node* np) {
    if(np != NULL) {
        freeNode(np->prev);
        freeNode(np->next);
        free(np);
    }
}

void freeBucket(struct bucket* bp) {
    if(bp != NULL) {
        freeNode(bp -> head);
    }
    free(bp);
}

//  hash function with %
int hashFunction(int key){
    return key % BUCKET_SIZE;
}

//  insert a new key
void add(int key, int value){
    int hashIndex = hashFunction(key);

    // Add your code here
    // Create a new node
    struct node* node = createNode(key, value);

    // hashTable[hashIndex] is empty
    if (hashTable[hashIndex].count == 0) {
        hashTable[hashIndex].head = node;
        hashTable[hashIndex].count++;
    } else {
        // Link the new node to the linked list and update the head as new node
        node -> next = hashTable[hashIndex].head;
        hashTable[hashIndex].head -> prev = node;
        hashTable[hashIndex].head = node;
        hashTable[hashIndex].count++;
    }

    return;
}

// remove a key
void remove_key(int key){
    int hashIndex = hashFunction(key);

    // Add your code here
    struct node* pointer = hashTable[hashIndex].head;

    while(pointer != NULL) {
        if (pointer->key == key) {
            if (pointer -> prev != NULL) {
                pointer -> prev -> next = pointer -> next;
            }
            if (pointer -> next != NULL) {
                pointer -> next -> prev = pointer -> prev;
            }
            if (pointer == hashTable[hashIndex].head) {
                hashTable[hashIndex].head = pointer -> next;
            }
            hashTable[hashIndex].count--;
            printf("Key [%d] is removed.\n", key);
            free(pointer);
            return;
        }
        pointer = pointer -> next;
    }
    printf("Key [%d] does not exist.\n", key);

    return;
}

// search a value using a key
void search(int key){
    int hashIndex = hashFunction(key);
    struct node* node = hashTable[hashIndex].head;

    // Add your code here
    while (node != NULL && node -> key != key){
        node = node -> next;
    }

    if (node == NULL) {
        printf("Key [%d] does not exist.\n", key);
    } else {
        printf("The value of key [%d] is [%d].\n", node -> key, node -> value);
    }
    return;
}

void display(){
    struct node* iterator;

    printf("\n========= display start ========= \n");
    for (int i = 0; i<BUCKET_SIZE; i++){
        iterator = hashTable[i].head;
        printf("Bucket[%d] : ", i);
        while (iterator != NULL)
        {
            printf("(key: %d, val: %d)  <-> ", iterator->key, iterator->value);
            iterator = iterator->next;
        }
        printf("\n");
    }
    printf("\n========= display complete ========= \n");
}

int main(){
    hashTable = (struct bucket *)malloc(BUCKET_SIZE * sizeof(struct bucket));

    add(0, 1);
    add(1, 10);
    add(11, 12);
    add(21, 14);
    add(31, 16);
    add(5, 18);
    add(7, 19);

    display();

    remove_key(31);
    remove_key(11);

    display();

    remove_key(1);
    remove_key(11);

    display();

    remove_key(21);

    display();

    search(11);
    search(1);

    freeBucket(hashTable);

}
