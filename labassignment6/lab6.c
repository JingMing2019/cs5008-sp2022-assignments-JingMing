//Jing Ming
//ming.j@northeastern.edu

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* function to encrypt the data*/
void encrypt(char text[], int key) {

    //insert your code here
    for (int i = 0; i < strlen(text); i++) {
    	if (isupper(text[i])) {
    	    text[i] = (text[i] - 'A' + key) % 26 + 'A';
    	} else {
    	    text[i] = (text[i] - 'a' + key) % 26 + 'a';
    	}
    }
}

/*function to decrypt the data*/
void decrypt(char text[],int key){

    //insert your code here
    for (int i = 0; i < strlen(text); i++) {
        if (isupper(text[i])) {
            text[i] = (text[i] - 'A' - key + 26) % 26 + 'A';
        } else {
            text[i] = (text[i] - 'a' - key + 26) % 26 + 'a';
        }
    }
}


/*----------- Main program---------------*/
int main()
{
    char text[20] ;
    int keyvalue=3;
    /*Input string */
    printf("Enter the message:  ");
    scanf("%s",text);
    printf("text input   = %s\n",text);

    /*call function to encrypt the data*/
    encrypt(text,keyvalue);
    printf("Encrypted value = %s\n",text);

    /*call function to decrypt the data*/
    decrypt(text,keyvalue);
    printf("Decrypted value = %s\n",text);

    return 0;
}
