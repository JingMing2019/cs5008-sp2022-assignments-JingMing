// name: Jing Ming
// email: ming.j@northeastern.edu
// C program to implement queue using arrays

#include <stdio.h>
#define N 8 //Max. capacity of Queue

int arr[N];
int rear = -1;
int front = -1;


/*----To check if the queue is empty-------*/
int isempty() {
    return rear == -1;
}

/*-----To check if the queue is full----------*/
int isfull() {
    return rear == N - 1;
}

/*---- To see the data at the front of the queue---*/
int peek()
{
    if(isempty()){
        printf("Queue is empty.\n");
        return -1;
    }
    return arr[0];
}

/*---To insert the elements into the queue------*/
void enqueue(int data) {
 //insert your code here
    if (isfull()) {
	    printf("Queue is full.\n");
     	return;
    }
    if (isempty()) {
        front++;
    }
    rear++;
    arr[rear] = data;
    printf("Enqueued data is: %d\n", arr[rear]);
}

/*----Function to remove the elements from the queue----*/
int dequeue() {
    //insert your code here
    if(isempty()){
        printf("Queue is empty.\n");
        return -1;
    }
    int top = arr[front];
    int i;

    if(front == rear) {
        front--;
    } else {
        for (i = front; i < rear; i++) {
        	arr[i] = arr[i + 1]; // move the remaining part forward
        }
    }
    rear--;
    return top;
}

/*---Function to display the elements of the queue-------*/
void display()
{
    if(isempty()) {
        printf("Queue is empty\n");
        return;
    }
    int i;
    for(i = front; i <= rear; i++) {
        printf("%d ", arr[i]);
    }
}

/*-----Main program-----*/
int main()
    {
    /* insert 8 items */
    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);
    enqueue(5);
    enqueue(6);
    enqueue(7);
    enqueue(8);
    display();
    printf("\n");
    enqueue(9);
    int i;
    for(i = 0;i < N; i++){
        printf("dequeued element is: %d\n",dequeue());
    }
    display();
    printf("\n");
    printf("The element at the front of the queue is: %d\n",peek());
    enqueue(1);
    enqueue(2);
    display();
    return 0;
    }

