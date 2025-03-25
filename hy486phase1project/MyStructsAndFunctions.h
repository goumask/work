#ifndef MYSTRUCTSANDFUNCTIONS_H
#define MYSTRUCTSANDFUNCTIONS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

// Needed for exponential backoff
#define MIN_DELAY 5
#define MAX_DELAY 15

// Needed for prime number calculation
const int MAX_SIZE = 1e4;
int hashTableSize;
 
 struct DLLNode {
	 int productID;
	 pthread_mutex_t lock;
	 struct DLLNode *next;
	 struct DLLNode *prev;
};

struct LinkedList{
	 struct DLLNode *head;
	 struct DLLNode *tail;
};

struct HTNode{
	 int productID;
	 pthread_mutex_t lock;
};

struct stackNode{
	int productID;
	struct stackNode *next;
};

// Declare structures
struct LinkedList myLinkedList;
struct HTNode **myHashTables;
struct stackNode *Top;

// For stack functions (from lectures) - Atomic Compare&Swap
int CAS(struct stackNode* old, struct stackNode* n) { // Top is explicit
	struct stackNode* tmp = Top;
	
	if (Top == old) {
		Top = n;
		return 1;
	}
	return 0;
}

// For stack functions (from lectures)
void BackOff() {
	static int limit = MIN_DELAY;
	srand(time(NULL));
	int delay = rand() % limit;
	// if 0 < limit < 32, that many low-order bits of the
	// returned value will be independently chosen bit
	//values
	if (MAX_DELAY < 2 * limit) {
		limit = MAX_DELAY;
	}
	else {
		limit = 2 * limit;
	}
	usleep(delay);
}

// For stack functions (from lectures)
int tryPush(struct stackNode *n) {
	
	struct stackNode * oldTop = Top;
	n->next = oldTop;
	
	if (CAS(oldTop, n)) {
		return 1;
	}
	else return 0;
}

// For stack functions (from lectures)
void push(int id) {
	struct stackNode *n = (struct stackNode *) malloc(sizeof(struct stackNode));
	n->productID = id;
	
	while (1) {
		if (tryPush(n))
			return;
		else BackOff();
	}
}

// For stack functions (from lectures)
struct stackNode *TryPop(void) {
	struct stackNode *oldTop = Top;
	struct stackNode * newTop;
	if (oldTop == NULL)
		return NULL;
	newTop = oldTop->next;
	if (CAS(oldTop, newTop))
		return oldTop;
	else return NULL;
}

// For stack functions (from lectures)
int pop() {
	struct stackNode *rn;
	while (1) {
		rn = TryPop();
		if (rn == NULL)
			return -1;
		if (rn != NULL)
			return rn->productID;
		else BackOff();
	}
}

// Calculate stack size
int stackSizeCheck() {
	
	int sizeFound = 0;
	struct stackNode *temp = Top;
	while (temp != NULL) {
		sizeFound++;
		temp = temp->next;
	}
	return sizeFound;
}

// Calculate list size
int listSizeCheck() {
	
	int count = 0;
	struct DLLNode *curr;
	curr = myLinkedList.head;
	while (curr != NULL) {
		if (curr != myLinkedList.head && curr != myLinkedList.tail) {
			count++;
		}
		curr = curr->next;
	}
	return count;
}

// Calculate list keysum
int listKeysumCheck() {
	
	int sum = 0;
	struct DLLNode *curr;
	curr = myLinkedList.head;
	while (curr != NULL) {
		if (curr != myLinkedList.head && curr != myLinkedList.tail) {
			sum += curr->productID;
		}
		curr = curr->next;
	}
	return sum;
}

// Insert product id to the list as a new node
void listInsert(int id) {
	
	struct DLLNode *pred, *curr;
	pthread_mutex_lock(&myLinkedList.head->lock);
	pred = myLinkedList.head; 
	curr = pred->next; 
	pthread_mutex_lock(&curr->lock);
	while (curr->productID < id) { 
		pthread_mutex_unlock(&pred->lock);
		pred = curr; 
		curr = curr->next;
		pthread_mutex_lock(&curr->lock);
	}
	if (id != curr->productID) {
		struct DLLNode* newDLLNode;
		newDLLNode = (struct DLLNode*) malloc(sizeof(struct DLLNode));
		newDLLNode->productID = id;
		pthread_mutex_init(&newDLLNode->lock, NULL);
		newDLLNode->next = curr;
		newDLLNode->prev = pred;
		pred->next = newDLLNode; 
		curr->prev = newDLLNode;
	}
	pthread_mutex_unlock(&pred->lock);
	pthread_mutex_unlock(&curr->lock);
}

// Initialize List (Head & Tail)
void initializeList(int N) {
	
	struct DLLNode *newDLLNodeHead, *newDLLNodeTail;
	newDLLNodeHead = (struct DLLNode*) malloc(sizeof(struct DLLNode));
	newDLLNodeTail = (struct DLLNode*) malloc(sizeof(struct DLLNode));
	newDLLNodeHead->productID = -1;
	newDLLNodeTail->productID = N*N;
	pthread_mutex_init(&newDLLNodeHead->lock, NULL);
	pthread_mutex_init(&newDLLNodeTail->lock, NULL);
	myLinkedList.head = newDLLNodeHead;
	myLinkedList.tail = newDLLNodeTail;
	myLinkedList.head->next = myLinkedList.tail;
	myLinkedList.tail->prev = myLinkedList.head;
	myLinkedList.tail->next = NULL;
	myLinkedList.head->prev = NULL;
}

// Delete productID node from list
void listDelete(int id) {
	
	struct DLLNode *pred, *curr, *succ;
	pthread_mutex_lock(&myLinkedList.head->lock);
	pred = myLinkedList.head; 
	curr = pred->next; 
	pthread_mutex_lock(&curr->lock);
	while (curr->productID < id) { 
		pthread_mutex_unlock(&pred->lock);
		pred = curr; 
		curr = curr->next;
		pthread_mutex_lock(&curr->lock);
	}
	if (id == curr->productID) {
		succ = curr->next;
		pthread_mutex_lock(&succ->lock);
		pred->next = succ;
		succ->prev = pred;
		pthread_mutex_unlock(&succ->lock);
	}
	pthread_mutex_unlock(&pred->lock);
	pthread_mutex_unlock(&curr->lock);
}

// Based on https://www.tutorialspoint.com/kth-prime-number-greater-than-n-in-cplusplus
void findAllPrimes(int* prime) {
	
   
   for (int p = 2; p * p <= MAX_SIZE; p++) {
      if (prime[p]) {
         for (int i = p * p; i <= MAX_SIZE; i += p) {
            prime[i] = 0;
         }
      }
   }
}

// Based on https://www.tutorialspoint.com/kth-prime-number-greater-than-n-in-cplusplus
int findPrimeGreaterThan(int floor) {
	
	int prime[MAX_SIZE + 1];
	for (int i = 0; i < MAX_SIZE; i++) {
		prime[i] = 1;
	}
	findAllPrimes(prime);
	for (int i = floor + 1; i < MAX_SIZE; i++) {
      if (prime[i]) {
         return i;
      }
   }
   return -1;
}

// Memory allocation for Hash Tables. Size: appropriate prime
void initializeHashTables(int N, int M) {
	
	int i, j;
	hashTableSize = findPrimeGreaterThan(3 * N);
	myHashTables = (struct HTNode**) malloc(M * sizeof(struct HTNode*));
	for (i = 0; i < M; i++) {
		myHashTables[i] = (struct HTNode*) malloc(hashTableSize * sizeof(struct HTNode));
		for (j = 0; j < hashTableSize; j++) {
			myHashTables[i][j].productID = -1;
			pthread_mutex_init(&myHashTables[i][j].lock, NULL);
		}
	}
}

// Insert productID to proper Hash table, K = id % N, h1(K) = K, h2(K) = K
void HTInsert(int N, int id, int consumerNumber) {
	
	int K = id % hashTableSize, p = K, temp;
	pthread_mutex_lock(&myHashTables[consumerNumber][p].lock);
	while (myHashTables[consumerNumber][p].productID != -1) {
		if (myHashTables[consumerNumber][p].productID > id) {
			temp = myHashTables[consumerNumber][p].productID;
			myHashTables[consumerNumber][p].productID = id;
			id = temp;
		}
		pthread_mutex_unlock(&myHashTables[consumerNumber][p].lock);
		p = (p + K) % hashTableSize;
		pthread_mutex_lock(&myHashTables[consumerNumber][p].lock);
	}
	myHashTables[consumerNumber][p].productID = id;
	pthread_mutex_unlock(&myHashTables[consumerNumber][p].lock);
}

// Delete random productID from Hash Table
int HTDelete(int N, int consumerNumber) {
	
	int K, p, deletedProductID = -1;
	srand(time(NULL));
	K = rand() % hashTableSize;
	p = K;
	pthread_mutex_lock(&myHashTables[consumerNumber][p].lock);
	while (myHashTables[consumerNumber][p].productID == -1) {
		pthread_mutex_unlock(&myHashTables[consumerNumber][p].lock);
		p = (p + K) % hashTableSize;
		pthread_mutex_lock(&myHashTables[consumerNumber][p].lock);
	}
	deletedProductID = myHashTables[consumerNumber][p].productID;
	myHashTables[consumerNumber][p].productID = -1;
	pthread_mutex_unlock(&myHashTables[consumerNumber][p].lock);
	
	return deletedProductID;
}

#endif