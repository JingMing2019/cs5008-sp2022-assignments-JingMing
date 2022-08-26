/*C Program to read and print the employee details using structure and dynamic memory allocation*/
#include <stdio.h>
#include <stdlib.h>
/*structure to hold the details of an employee*/
typedef struct employee
{
    int empId;
    char Name[100];
    char Designation[100];
    char Dept[10];

}employee_t;

/* Read the employee details using scanf*/
void readData(int n, employee_t* s)
{
    int i;
    for (i = 0; i < n; i++) {
    	int id = i + 1;
    	printf("Enter the employeeID, Name, Designation and Department of Employee %d\n", id);
    	scanf("%d", &s[i].empId);
    	scanf("%99s", s[i].Name); // properway to scan a string, left 1 more space for the '\0' null to indicate the end of the string.
    	scanf("%99s", s[i].Designation);
    	scanf("%99s", s[i].Dept);
    }
    return;
}
/* Function to print the employee details*/
void display(int n, employee_t* s)
{
    int i;
    for (i = 0; i < n; i++) {
    	printf("The details of Employee %d:\n", i + 1);
        printf("empId: %d\n", s[i].empId);  //s[i] represents one employee_t, a struct, not a pointer
    	printf("Name: %s\n", s[i].Name);
    	printf("Designation: %s\n", s[i].Designation);
    	printf("Dept: %s\n", s[i].Dept);
    }
    return;
}

/*----------Main Program--------*/
int main()

{
    int n;
    printf("Enter the number of employees: \n");
    scanf("%d", &n);
    employee_t* s = (employee_t*)malloc(n * sizeof(employee_t));

    readData(n, s);
    display(n, s);
    free(s);   
    return 0;
}

