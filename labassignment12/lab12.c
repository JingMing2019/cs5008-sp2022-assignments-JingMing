// ming.j@northeastern.edu
// Jing Ming
// longeast common prefix
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

void longestCommonPrefix(char arr[][20], int m, char res[20]){

    //insert your code here
    int index = 0;
    int n = strlen(arr[0]);
    int i, j;

    for(i = 0; i < n; i++) {
    	char c = arr[0][i];
    	bool flag = true;
    	for(j = 1; j < m; j++) {
    	    if(c != arr[j][i]) {
    		flag = false;
    		break;
    	    }
    	}
    	if(flag == false){
    	    break;
    	} else {
    	    res[index] = c;
    	    index++;
    	}
    }
}

int main(){
    char arr[5][20] = {"aaabc", "aaanv", "aaamk", "aaavf", "aaacf"}; // input
    char res[20]; // store output
    int m = sizeof(arr)/sizeof(arr[0]); // number of words in an array
    int i;

    longestCommonPrefix(arr, m, res);

    printf("The Longest Common Prefix is ");

    for(i = 0; i < strlen(res); i++){
	   printf("%c", res[i]);
    }
    printf("\n");

    return 0;
}

