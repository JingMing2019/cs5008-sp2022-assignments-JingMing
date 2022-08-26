//Jing Ming
//ming.j@northeastern.edu
#include<stdio.h>
int main()
{
    int a,b,c, choice;

    printf("Enter your choice\n");
    printf(" 1.addition\n 2. Subtraction\n 3. Multiplication\n 4. Division\n");
    scanf("%d",&choice);
 
    printf("Enter a and b values");
    scanf("%d %d", &a, &b);

    switch (choice) {
    case (1):
		printf("Addition\n");
		c = a + b;
		printf("Sum = %d\n", c);
		break;
    case (2):
		printf("Subtrction\n");
		c = a - b;
		printf("Difference = %d\n", c);
		break;
    case (3):
		printf("Multiplication\n");
		c = a * b;
		printf("Product = %d\n", c);
		break;
    case (4):
		printf("Division\n");
		if (a == 0) {
		    printf("Warning: division by zero\n");
		    break;
	        }
		c = b / a;
		printf("Quotient = %d\n", c);
		break;
    default:
		printf("Invalid Option\n");
    }

    return 0;
}
