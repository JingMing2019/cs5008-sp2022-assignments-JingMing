// name: Jing Ming
// email: ming.j@northeastern.edu
// FSM parse input from a file

// format of document is a bunch of data lines beginning with an integer (rank which we ignore)
// then a ',' followed by a double-quoted string (city name)
// then a ',' followed by a double-quoted string (population) - ignore commas and covert to int; or (X) - convert to 0
// then a lot of entries that are ignored


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAXSTRING 200

// finite state machine states
#define STARTSTATE 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define ACCEPTSTATE 10
#define ERRORSTATE 11

// check if a character c is a digit
bool isDigit(char c) {
  if ('0' <= c && c <= '9') {
    return true;
  } else {
    return false;
  }
}

// append character c to string s
void appendChar(char* s, char c) {
  char charToStr[2];           // convert char to string
    charToStr[0] = c;
    charToStr[1] = '\0';       // put `\0` to terminate string of one character
    strcat(s, charToStr);
}

int main () {

  char inputLine[MAXSTRING];   // temporary string to hold input line
  char cityStr[MAXSTRING];     // city name
  int  lineNum;                // line number (city rank)
  int  popInt;                 // population
  int  state;                  // FSM state
  int  nextChar;               // index of next character in input string
  char temp[MAXSTRING];        // temp string to build up extracted strings from input characters

  FILE* fp;
  fp = fopen("pop.csv","r");

  if (fp != NULL) {
    fgets(inputLine, MAXSTRING, fp); // read a line from the fp with MAXSTRING length and store it in the `inputLine`

    /* -------------------- BEGIN FINTITE STATE MACHINE -------------------- */

    // STARTSTATE: digit -> S1
    // S1: digit -> S1; , -> S2
    // S2: " -> S3
    // S3: !" -> S3; " -> S4
    // S4: , -> S5
    // S5: " -> S6; ( -> ACCEPTSTATE
    // S6: digit -> S6; , -> S6; " -> ACCEPTSTATE;
    // ACCEPTSTATE: done!
    // else go to ERRORSTATE
    //
    while (feof(fp) == 0){ //means not reach the End Of File

      nextChar = 0;
      state = STARTSTATE;
      strcpy(temp,"");       // temp = ""

      if (nextChar >= strlen(inputLine)){
				// if no input string then go to ERRORSTATE
				state = ERRORSTATE;
      }

      while ((state != ERRORSTATE) && (state != ACCEPTSTATE)) {
      	switch (state) {
					case STARTSTATE:
					// look a digit to confirm a valid line
						if (isDigit(inputLine[nextChar])) {
							state = S1;
							lineNum = inputLine[nextChar] - '0';
						} else {
							state = ERRORSTATE;
						}
						break;


					// ADD YOUR CODE HERE
					case S1:
					// look a digit or comma to confirm a valid line
						if (isDigit(inputLine[nextChar])) {
							state = S1;
							int digit = inputLine[nextChar] - '0';
							lineNum = lineNum * 10 + digit;
						} else if (inputLine[nextChar] == ',') {
							state = S2;
							strcpy(temp, "");
						} else {
							state = ERRORSTATE;
						}
						break;

						case S2:
							// look a " to confirm a valid line
							if (inputLine[nextChar] == '\"') {
								state = S3;
							} else {
								state = ERRORSTATE;
							}
							break;

						case S3:
							// look a " to chage to next state, else stay in S3
							if (inputLine[nextChar] != '\"') {
								state = S3;
								appendChar(temp, inputLine[nextChar]);
							} else {
								state = S4;
								strcpy(cityStr, temp);
								strcpy(temp, "");
							}
							break;

						case S4:
							// look a comma to confirm a valid line
							if (inputLine[nextChar] == ',') {
								state = S5;
							} else {
								state = ERRORSTATE;
							}
							break;

						case S5:
							// look a " or ( to confirm a valid line
							if (inputLine[nextChar] == '\"') {
								state = S6;
								popInt = 0;
							} else if (inputLine[nextChar] == '(') {
								state = ACCEPTSTATE;
								popInt = 0;
							} else {
								state = ERRORSTATE;
							}
							break;

						case S6:
							// look a digit or , or " to confirm a valid line
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
							// nothing to do - we are done!
							break;

						default:
							state = ERRORSTATE;
							break;
					} // end switch

					// advance input
					nextChar++;

      	}	// end while state machine loop

				// process the line - print out raw line and the parsed fields
				printf("> %.60s\n", inputLine);
				printf("%d, [%.30s]: %d\n", lineNum, cityStr, popInt);

				// get next line
				fgets(inputLine, MAXSTRING, fp);

    } // end while file input loop
		fclose(fp);

		/* -------------------- END FINTITE STATE MACHINE -------------------- */

  } else {
    printf("File not found!\n");
  }

  return 0;
}
