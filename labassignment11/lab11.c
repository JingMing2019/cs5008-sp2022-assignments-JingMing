// Jing Ming
// ming.j@northeastern.edu
// Dining Philosophers Problem using Thread
// gcc -lpthread lab11.c -o lab11

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t chopstick[5];//lock variable shared

// Thread to be executed
void* philosopher(void* x) {
    //Treat variable x as a pointer to an int and then extract the value into n
    int* a = (int*)x; // type casting
    int n = *a;       // n--philosopher number and chopsticks

    /*-----Insert your code here----*/
	printf("Philosopher %d is thinking.\n", n + 1);
	pthread_mutex_lock(&chopstick[n]);                     // Put the mutex lock for the left chopstick
	pthread_mutex_lock(&chopstick[(n + 1) % 5]);           // Put the mutex lock for the right chopstick
    // Print the philosopher (number) is eating with the chopstick (numbers) left and right
  	printf("Philosopher %d is eating using chopstick[%d] and chopstick[%d].\n", n + 1, n, (n + 1) % 5);
	sleep(1);                                              // sleep for some time
	printf("Philosopher %d is finished eating.\n", n + 1); // Print the philosopher (number) is finished eating.
	pthread_mutex_unlock(&chopstick[n]);                   // Unlock the mutex lock for the left chopstick
	pthread_mutex_unlock(&chopstick[(n + 1) % 5]);         // Unlock the mutex lock for right chopstick

    return NULL;

}


/*------------ Main Program---------*/
int main(){
    pthread_t threads[5];
    int i;
    int val[5];

    //initializing the mutex
    for(i = 0; i < 5; i++){
        pthread_mutex_init(&chopstick[i], NULL);
    }

    //create and run the thread
    for(i = 0; i < 5; i++) {
        val[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &val[i]);
    }

    //wait until all the threads are done
    for(i = 0; i < 5; i++){
        pthread_join(threads[i], NULL);
    }

    // Destroying the mutex
    for(i = 0; i < 5; i++){
        pthread_mutex_destroy(&chopstick[i]);
    }
    return 0;
}
