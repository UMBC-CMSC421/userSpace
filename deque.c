#include "deque.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Test
// Global Variables for the Deque and Synchronization
deque_421_t *deque = NULL;
sem_t sem_high;
sem_t sem_medium;
sem_t sem_low;
pthread_mutex_t deque_mutex = PTHREAD_MUTEX_INITIALIZER;

/*
 * Function: init_deque
 * --------------------
 * Purpose: Initializes the deque with three separate priority queues.
 */
int init_deque(void)
{
    // TODO: Allocate memory for the deque structure
    // TODO: Initialize all the pointers (high_head, high_tail, etc.) to NULL
    // TODO: Set all counts (high_count, medium_count, low_count) to zero
    // TODO: Initialize the semaphores and mutex
    
    deque = malloc(sizeof(struct deque_421_t));
    deque->high_head = NULL;
    deque->high_tail = NULL;
    deque->medium_head = NULL;
    deque->medium_tail = NULL;
    deque->low_head = NULL;
    deque->low_tail = NULL;
    
    high_count = 0;
    medium_count = 0;
    low_count = 0;
    
    //we want them to be shared by threads, so init with 0
    sem_init(sem_high, 0, high_count);
    sem_init(sem_medium, 0, medium_count);
    sem_init(sem_low, 0, low_count);
    
    deque_mutex = PTHREAD_MUTEX_INITIALIZER;
    
    return 0;
}

/*
 * Function: enqueue_front
 * -----------------------
 * Purpose: Adds a data block to the front of the specified priority queue.
 */
int enqueue_front(char *data, int priority)
{
    // TODO: Lock the mutex
    // TODO: Create a new node and copy the data into it
    // TODO: Insert the node at the front of the corresponding priority queue
    // TODO: Update the head and tail pointers as needed
    // TODO: Unlock the mutex and signal the corresponding semaphore
    
    //locking mutex
    pthread_mutex_lock(deque_mutex);
    
    struct node *newNode = {NULL, NULL, &data}; //i feel like this is wrong
    
    if (priority == HIGH_PRIORITY) {
    	if (deque->high_head == NULL) { //list is empty
    		deque->high_head = newNode;
    		//deque->high_head->next = deque-> high_tail;
    		deque->high_tail = newNode;
    	}
    	else {
    		newNode->next = deque->high_head;
    		deque->high_head->prev = newNode;
    		deque->high_head = newNode;
    	}
    	
    	sem_signal(sem_high);
    }
    else if (priority == MEDIUM_PRIORITY) {
    	if (deque->medium_head == NULL) {
    		deque->medium_head = newNode;
    		deque->medium_tail = newNode;
    	}
    	else {
    		newNode->next = deque->medium_head;
    		deque->medium_head->prev = newNode;
    		deque->medium_head = newNode;
    	}
    	
    	sem_signal(sem_medium); //do we need to call sem_wait?
    }
    else if (priority == LOW_PRIORITY) {
    	if (deque->low_head == NULL) {
    		deque->low_head = newNode;
    		deque->low_tail = newNode;
    	}
    	else {
    		newNode->next = deque->low_head;
    		deque->low_head->prev = newNode;
    		deque->low_head = newNode;
    	}
    	
    	sem_signal(sem_low);
    }
    else {
    	//that is an error
    }
    
    //unlock
    pthread_mutex_unlock(deque_mutex);
    return 0;
}

/*
 * Function: enqueue_rear
 * ----------------------
 * Purpose: Adds a data block to the rear of the specified priority queue.
 */
int enqueue_rear(char *data, int priority)
{
    // TODO: Implement similar logic as enqueue_front, but insert at the rear
    
    //locking mutex
    pthread_mutex_lock(deque_mutex);
    
    struct node *newNode = {NULL, NULL, &data}; //i feel like this is wrong
    
    if (priority == HIGH_PRIORITY) {
    	if (deque->high_head == NULL) { //list is empty
    		deque->high_head = newNode;
    		deque->high_tail = newNode;
    	}
    	else {
    		newNode->prev = deque->high_tail;
    		deque->high_tail->next = newNode;
    		deque = high_tail = newNode;
    	}
    	
    	sem_signal(sem_high);
    }
    else if (priority == MEDIUM_PRIORITY) {
    	if (deque->medium_head == NULL) {
    		deque->medium_head = newNode;
    		deque->medium_tail = newNode;
    	}
    	else {
    		newNode->prev = deque->medium_tail;
    		deque->medium_tail->next = newNode;
    		deque = medium_tail = newNode;
    	}
    	
    	sem_signal(sem_medium); //do we need to call sem_wait?
    }
    else if (priority == LOW_PRIORITY) {
    	if (deque->low_head == NULL) {
    		deque->low_head = newNode;
    		deque->low_tail = newNode;
    	}
    	else {
    		newNode->prev = deque->low_tail;
    		deque->low_tail->next = newNode;
    		deque = low_tail = newNode;
    	}
    	
    	sem_signal(sem_low);
    }
    else {
    	//that is an error
    }
    
    //unlock
    pthread_mutex_unlock(deque_mutex);
    return 0;
}

/*
 * Function: dequeue_front
 * -----------------------
 * Purpose: Removes a data block from the front of the highest-priority queue available.
 */
int dequeue_front(char *data)
{
    // TODO: Check high, then medium, then low queues
    // TODO: Lock the mutex and remove the node from the front of the queue
    // TODO: Copy the data to the provided buffer
    // TODO: Update pointers and counts, unlock the mutex, and return
    return 0;
}

/*
 * Function: dequeue_rear
 * ----------------------
 * Purpose: Removes a data block from the rear of the highest-priority queue available.
 */
int dequeue_rear(char *data)
{
    // TODO: Implement similar logic as dequeue_front, but remove from the rear
    return 0;
}

/*
 * Function: delete_deque
 * ----------------------
 * Purpose: Deletes all elements in the deque and frees allocated memory.
 */
int delete_deque(void)
{
    // TODO: Traverse and free all nodes for each priority queue
    // TODO: Free the main deque structure and destroy the semaphores/mutex
    return 0;
}
