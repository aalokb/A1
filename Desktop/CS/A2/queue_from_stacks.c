/*
 * This is the file in which you'll write the functions required to implement
 * a queue using two stacks.  Make sure to add your name and @oregonstate.edu
 * email address below:
 *
 * Name: Aalok Borkar	
 * Email: borkaraa@oregonstate.edu
 */
#ifndef __QUEUE_FROM_STACKS_C
#define __QUEUE_FROM_STACKS_C

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "link.h"
#include "stack.h"
#include "queue_from_stacks.h"
 


/*
 * This function should allocate and initialize all of the memory needed for
 * your queue and return a pointer to the queue structure.
 */
struct queue_from_stacks* queue_from_stacks_create() {
	struct queue_from_stacks *q_ptr = malloc(sizeof(struct queue_from_stacks));
	q_ptr->s1 = stack_create();
    q_ptr->s2 = stack_create();
    return q_ptr; //creates and returns a fully allocated NULL initialized queue.
}
/*
 * This function should free all of the memory allocated to a queue, including
 * the memory associated with each stack.
 *
 * Params:
 *   queue - the queue to be destroyed.  May not be NULL.  The function should
 *     exit the program with an error if queue is NULL.
 */
void queue_from_stacks_free(struct queue_from_stacks* queue) {
	assert(queue); //if Queue is empty throw an error and exit program;
	assert(queue->s1); //if stack pointers dont even point to a stack
	assert(queue->s2);

	while(!stack_isempty(queue->s1)){ //while its not empty
		stack_pop(queue->s1);
	}
	while(!stack_isempty(queue->s2)){ //while its not empty
		stack_pop(queue->s2);
	}
	free(queue->s1);
	free(queue->s2);
	free(queue);
}

/*
 * This function should return 1 if a queue is completely empty or 0 if there
 * is at least one element stored in the queue.
 *
 * Params:
 *   queue - the queue whose emptiness is to be checked.  May not be NULL.
 *     The function should exit the program with an error if queue is NULL.
 *
 * Return:
 *   Should return 1 if the queue is empty or 0 otherwise.
 */
int queue_from_stacks_isempty(struct queue_from_stacks* queue) { //WORK IN PROGRESS
	assert(queue); //if Queue is empty throw an error and exit program;
	assert(queue->s1); //if stack pointers dont even point to a stack
	assert(queue->s2);

	if(stack_isempty(queue->s1) && stack_isempty(queue->s2)){ //both inner-stacks are empty then queue is fully empty
		return 1;
	}
	return 0;
}

/*
 * Should enqueue a new value onto the end of a queue.
 *
 * Params:
 *   queue - the queue onto which to enqueue a value.  May not be NULL.
 *     The function should exit the program with an error if queue is NULL.
 *   value - the new value to be enqueueed onto the queue
 */
void queue_from_stacks_enqueue(struct queue_from_stacks* queue, int value) { 
	//if stack 1 is empty: run the loop that pops s2 and pushes the popped value onto s1 while temp is != NULL etc.   This statement is assuming one transfer has been done and all elements are in s2 (in reverse order)
			//Loop this while (queue->s2->top != NULL): stack_push(queue->s1, stack_pop(queue->s2));
	//once done: enqueue
	assert(queue); //if Queue is empty throw an error and exit program;
	assert(queue->s1); //if stack pointers dont even point to a stack
	assert(queue->s2);
	if(stack_isempty(queue->s1)){//if the stack 1 IS empty
		while (!stack_isempty(queue->s2)){//run this while s2 has content inside it | If this is a first time enqueue then this loop wont even run so its all good
			stack_push(queue->s1, stack_pop(queue->s2));
		}
	}//now s1 is full and has all the nodes in order for enqueue-ing
	stack_push(queue->s1, value);
}

/*
 * Should return a queue's front value without removing that value from the
 * queue.
 *
 * Params:
 *   queue - the queue from which to read the front value.  May not be NULL or
 *     empty.  The function should exit the program with an error if queue is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the front of the queue.
 */
int queue_from_stacks_front(struct queue_from_stacks* queue) {
  //if s1 is empty(return the last element of s2)
  //else if s2 is empty(return first element of s1)
	assert(queue); //if Queue is empty throw an error and exit program;
	assert(queue->s1); //if stack pointers dont even point to a stack
	assert(queue->s2);
	assert(!queue_from_stacks_isempty(queue));

	if(stack_isempty(queue->s2)){
		while (!stack_isempty(queue->s1)){//run this while s2 has content inside it | If this is a first time enqueue then this loop wont even run so its all good
				stack_push(queue->s2, stack_pop(queue->s1));
		}
	} //get it into s2 so the order is front -> last
	return stack_top(queue->s2); //simply return the first value since the queue is ordered correctly

}
 
/*
 * Should remove the front element from a queue and return its value.
 *
 * Params:
 *   queue - the queue from which to dequeue a value.  May not be NULL or
 *     empty.  The function should exit the program with an error if queue is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the front of the queue before that value
 *   is dequeued.
 */
int queue_from_stacks_dequeue(struct queue_from_stacks* queue) {
  //if stack 2 is empty: run the loop that pops s1 and pushes the popped value onto s2 while temp is != top etc.
  //once done: dequeue
	assert(queue); //if Queue is empty throw an error and exit program;
	assert(queue->s1); //if stack pointers dont even point to a stack
	assert(queue->s2);
	if(stack_isempty(queue->s2)){
		while (!stack_isempty(queue->s1)){//run this while s2 has content inside it | If this is a first time enqueue then this loop wont even run so its all good
			stack_push(queue->s2, stack_pop(queue->s1));
		}
	}
	return stack_pop(queue->s2);
}

#endif