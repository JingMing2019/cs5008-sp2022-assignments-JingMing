// name: Jing Ming
// email: ming.j@northeastern.edu


// please start with a copy of your hw7.c, rename it to hw.8
// and then complete the assignment
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define HASH_TABLE_SIZE 400
#define STRLENGTH 400
// Finite state machine states
#define STARTSTATE 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define ACCEPTSTATE 10
#define ERRORSTATE 11


//===================================== Node =================================================
// Single linked list node
typedef struct node {
    char key[STRLENGTH]; //store city, state name. Attention: not the char pointer!
    int value;  	 //store population
    struct node* next;

} node_type;

// Create new node
node_type* new_node(char* key, int value) {
    node_type* newNode = (node_type*)malloc(sizeof(node_type));
    if (newNode != NULL) {
        // Attention: key in new node is not a pointer, has to copy the string
        strcpy(newNode -> key, key);
        newNode -> value = value;
        newNode -> next = NULL;
    }

    return newNode;
}

// Free node
// Fragile assumption: this function does not free up nodes pointed to by next pointer
void freeNode(node_type* node_t) {
    if (node_t != NULL) {
	free(node_t);
    }
}




//============================= Bucket used in hash table ====================================
typedef struct bucket {
    node_type* head;     //each bucket stores a head of linked list

} bucket_type;

// Free bucket
void freeBucket(bucket_type* bucket_t) {
    if (bucket_t != NULL) {
	node_type* temp;
	while (bucket_t -> head != NULL) {
	    temp = bucket_t -> head;
	    bucket_t -> head = bucket_t -> head -> next;
	    freeNode(temp);
	}
    }
}



//============================= Helper Function ==============================================
// Determine whether the char is a digit or not
bool isDigit(char chr) {
    if (chr < '0' || chr > '9') {
	return false;
    } else {
	return true;
    }
}


// Append a char to the string
// Attention: do not simply use strcat, res is a char, not string 
void appendChar(char* dest, char res) {
    char chrToStr[2];
    chrToStr[0] = res;
    chrToStr[1] = '\0';
    strcat(dest, chrToStr);
}



//=========================== Hash Function ==================================================
// Hash function 1: length of city name modulo hash table size
int hash_function_1(char* cityName) {
    int length = strlen(cityName);
    int index = length % HASH_TABLE_SIZE;

    return index;

}

// Hash function 2: sum of chars in city name modulo hash table size
int hash_function_2(char* cityName) {
    int sumCityName = 0;
    int i;
    for(i = 0; i < strlen(cityName); i++) {
	sumCityName += cityName[i];
    }
    int index = sumCityName % HASH_TABLE_SIZE;

    return index;
}

// Hash function 3: product of first 2 chars in city name modulo hash table size
int hash_function_3(char* cityName) {
    int productChar = cityName[0] * cityName[1];
    int index = productChar % HASH_TABLE_SIZE;

    return index;
}



//============================ Update hash table ============================================
int update_hash_table(bucket_type* hashTable, int hashFuncNum, char* key, int value) {
    // Calculate the hash index according to the hashFuncNum
    int hashIndex;

    switch (hashFuncNum) {
	case 1:
	    hashIndex = hash_function_1(key);
	    break;

        case 2:
            hashIndex = hash_function_2(key);
            break;

	case 3:
            hashIndex = hash_function_3(key);
            break;

 	default:
	    printf("There does not exit No.%d hash function.\n", hashFuncNum);
	    return -1;
    }

    // Create new node
    node_type* newNode = new_node(key, value);

    // If the bucket is empty, make new node as head
    if (hashTable[hashIndex].head == NULL) {
	   hashTable[hashIndex].head = newNode;
    } else { // The bucket is not empty. New node point to head and become head.
	   newNode -> next = hashTable[hashIndex].head;
	   hashTable[hashIndex].head = newNode;
    }

    return 0; 
}



//============================= Display hash table ===========================================
void display_hash_table(bucket_type* hashTable) {
    node_type* pointer;
    int i;
    for(i = 0; i < HASH_TABLE_SIZE; i++) {
	printf("TABLE[%d]: \n", i);
	pointer = hashTable[i].head;
	while (pointer != NULL) {
	    printf("key/value: [%s] / [%d]\n", pointer -> key, pointer -> value);
	    pointer = pointer -> next;
	}
	printf("\n");
    }

}



//============================== Free hash table =============================================
void free_hash_table(bucket_type* hashTable) {
    if (hashTable != NULL) {
        int i;
        for(i = 0; i < HASH_TABLE_SIZE; i++) {
            freeBucket(&hashTable[i]);
        }
        free(hashTable);
    }
}

int main() {
    // Allocate memory for three hash table
    bucket_type* hashTable1 = (bucket_type*)malloc(HASH_TABLE_SIZE * sizeof(bucket_type));
    bucket_type* hashTable2 = (bucket_type*)malloc(HASH_TABLE_SIZE * sizeof(bucket_type));
    bucket_type* hashTable3 = (bucket_type*)malloc(HASH_TABLE_SIZE * sizeof(bucket_type));

    char inputLine[STRLENGTH]; 	// temporary string to hold input line
    char cityName[STRLENGTH];  	// city/state name in string
    int lineNum;  		// rank of each line
    int popInt;   		// population of city/state
    int state;			// FSM state
    int nextChar;		// index of next char in input string
    char temp[STRLENGTH];	// temporary string to hold extracted string from input line
    FILE* fp;

    // Open pop.csv for reading
    fp = fopen("pop.csv", "r");

    if (fp == NULL) {
	printf("File not found\n");
        return -1;
    }

    // Get a new line, and assign to inputLine
    // While not reach the End-Of-File
    while ( fgets(inputLine, STRLENGTH, fp) ) {
	// Initialization
	strcpy(cityName, "");
	lineNum = 0;
	popInt = 0;
	state = STARTSTATE;
	nextChar = 0;
 	strcpy(temp, "");

  	//======================= Begin Finite State Machine =================================
	if (nextChar >= strlen(inputLine)) {
	    // If no input string, then go to ERRORSTATE
	    state = ERRORSTATE;
	}


	while (state != ACCEPTSTATE) {
	    switch (state) {
		// STARTSTATE: 0-9 -> S1
		case STARTSTATE:
		    if (isDigit(inputLine[nextChar])) {
                state = S1;
			 lineNum += inputLine[nextChar] - '0';
		    } else {
		    	state = ERRORSTATE;
     		    }
		    break;
		
		// S1: 0-9 -> S1, ',' -> S2
		case S1:
		    if (isDigit(inputLine[nextChar])) {
                        state = S1;
			lineNum = lineNum * 10 + inputLine[nextChar] - '0';
                    } else if (inputLine[nextChar] == ',' ) {
			state = S2;
		    }else {
                        state = ERRORSTATE;
                    }
		    break;	    

		// S2: '\"' -> S3
                case S2:
                    if ( inputLine[nextChar] == '\"') {
                     	state = S3;
                    } else {
                        state = ERRORSTATE;
                    }
                    break;

		// S3: !'\"' -> S3, '\"' -> S4
                case S3:
                    if (inputLine[nextChar] != '\"') {
                        state = S3;
			appendChar(temp, inputLine[nextChar]);
                    } else {
                        state = S4;
			strcpy(cityName, temp);
			strcpy(temp, "");
                    }
                    break;

		// S4: ',' -> S5
                case S4:
                    if (inputLine[nextChar] == ',') {
                        state = S5;
                    } else {
                        state = ERRORSTATE;
                    }
                    break;

		// S5: '\"' -> S6, '(' -> ACCEPTSTATE
                case S5:
                    if (inputLine[nextChar] == '\"') {
                        state = S6;
                    } else if (inputLine[nextChar] == '(') { 
 			state = ACCEPTSTATE;
		    } else {
                        state = ERRORSTATE;
                    }
                    break;

		// S6: 0-9 -> S6, ',' -> S6,'\"' -> ACCEPTSTATE
                case S6:
                    if (isDigit(inputLine[nextChar])) {
                        state = S6;
			int digit = inputLine[nextChar] - '0';
			popInt = popInt * 10 + digit;	 
		    } else if (inputLine[nextChar] == ',') {
			state = S6;
		    } else if (inputLine[nextChar] == '\"') {
			state = ACCEPTSTATE; 
		    } else {
                        state = ERRORSTATE;
                    }
                    break;

		case ACCEPTSTATE:
		    break;

                case ERRORSTATE:
                    printf("Input line %s is not in the correct format.\n", inputLine);
		    return -1;
		
		default:
		    state = ERRORSTATE;
		    break;
	    }
	    // Go to next char
	    nextChar++;		
	}
	//======================= End Finite State Machine ===================================	
    	// Put pair (key = city/state name, value = population) into each hash table
        update_hash_table(hashTable1, 1, cityName, popInt);
	update_hash_table(hashTable2, 2, cityName, popInt);
	update_hash_table(hashTable3, 3, cityName, popInt);

    }
   
    fclose(fp);

    //=========================== Display three hash table ===================================
    printf("***** HASH TABLE 1 *****\n\n");
    printf("========================\n");
    display_hash_table(hashTable1);
    printf("========================\n\n\n");

    printf("***** HASH TABLE 2 *****\n\n");
    printf("========================\n");
    display_hash_table(hashTable2);
    printf("========================\n\n\n");
    
    printf("***** HASH TABLE 3 *****\n\n");
    printf("========================\n");
    display_hash_table(hashTable3);
    printf("========================\n\n\n");
    
    //============================ Free three hash table =====================================
    free_hash_table(hashTable1);
    free_hash_table(hashTable2);	             
    free_hash_table(hashTable3);

    return 0;
}

