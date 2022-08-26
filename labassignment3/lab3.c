// Jing Ming
// ming.j@northeastern.edu
// C program to check if the integer array contains duplicate elements.
#include<stdio.h>
#include<stdbool.h>

#define MAXSIZE 10

void bubble_sort(int* arr, int size) {
    int i, j, temp;

    for(i = 0; i < size - 1; i++) {
        for(j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return;
}

bool is_duplicate(int* arr, int size) {
    bool duplicate = false;
    int i;

    for(i = 0; i < size - 1; i++) {
        if(arr[i] == arr[i + 1]) {
            duplicate = true;
            break;
        }
    }

    return duplicate;
}

int main(){

    int arr[MAXSIZE];
    int i;
    printf("Please enter 10 numbers: ");
    for (i = 0; i < MAXSIZE; i++) {
        scanf("%d", &arr[i]);
    }

    printf("The input array is: ");
    for (i = 0; i < MAXSIZE; i++) {
        printf("%d", arr[i]);
        printf(" ");
    }
    printf("\n");
    int size = sizeof(arr) / sizeof(arr[0]);

    //insert your code here
    //call bubble sort function to sort the array
    bubble_sort(arr, size);

    //call is_duplication function to define whether the duplicate exits or not
    if (is_duplicate(arr, size) == true) {
        printf("The array has duplicate elements.\n");
    } else {
        printf("The array has no duplicate elements.\n");
    }

    return 0;
}
