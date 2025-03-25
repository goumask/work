// Kostas Goumas
// Compile gcc MyStructsAndFunctions.h prj1.c -o prj1 -lpthread
// Run ./prj1 3

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "MyStructsAndFunctions.h"

pthread_barrier_t   phaseBarrier; // the barrier synchronization object
int N, M;
struct args{int id;}; // For the thread run function args passing

void * threadFunction (void *myArgs) {
	
	int i, j;
	int myId = ((struct  args *)myArgs)->id;
	
	// Step 1
	for (i = 0; i < N; i++) {
		 listInsert(i * N + myId);
	}
	pthread_barrier_wait(&phaseBarrier); // Step 1 Barrier 1
	// Step 1 Check
	if(myId == 0) {
		int sizeFound, keysumFound;
		sizeFound = listSizeCheck();
		//listSizeCheck();
		printf("List size check (expected: %d, found: %d)\n", N * N, sizeFound);
		keysumFound = listKeysumCheck();
		printf("List keysum check (expected: %d, found: %d)\n", N * N * (N * N - 1) / 2, keysumFound);
		if (sizeFound != N * N || keysumFound != N * N * (N * N - 1) / 2) {
			// Terminate!!!!
		}
	}
    pthread_barrier_wait(&phaseBarrier); // Step 1 Barrier 2
	
	// Step 2
	int consumerNumber;
	for (i = 0; i < N; i++) {
		consumerNumber = i % M;
		listDelete(N * myId + i);
		HTInsert(N, N * myId + i, consumerNumber);
	}
	pthread_barrier_wait(&phaseBarrier); // Step 2 Barrier 1
	// Step 2 Check
	if(myId == 0) {
		int countHT, sumHT = 0;
		for (i = 0; i < M; i++) {
			countHT = 0;
			for (j = 0; j < hashTableSize; j++) {
				if (myHashTables[i][j].productID != -1) {
					countHT++;
					sumHT += myHashTables[i][j].productID;
				}
			}
			printf("HT[%d] size check (expected: %d, found: %d)\n", i, 3 * N, countHT);
		}
		printf("HT keysum check (expected: %d, found: %d)\n", N * N * (N * N - 1) / 2, sumHT);
		
	}
    pthread_barrier_wait(&phaseBarrier); // Step 2 Barrier 2
	
	// Step 3
	int deletedProductId;
	for (i = 0; i < M; i++) {
		consumerNumber = i % M;
		deletedProductId = HTDelete(N, consumerNumber);
		push(deletedProductId);
	}
	pthread_barrier_wait(&phaseBarrier); // Step 3 Barrier 1
	// Step 3 Check
	if(myId == 0) {
		for (i = 0; i < M; i++) {
			int countHT = 0;
			for (j = 0; j < hashTableSize; j++) {
				if (myHashTables[i][j].productID != -1) {
					countHT++;
				}
			}
			printf("HT[%d] size check (expected: %d, found: %d)\n", i, 2 * N, countHT);
		}
		int sizeFound;
		sizeFound = stackSizeCheck();
		printf("Stack size check (expected: %d, found: %d)\n", N * N / 3, sizeFound);
	}
    pthread_barrier_wait(&phaseBarrier); // Step 3 Barrier 2
	
	// Step 4
	int fixedProductId;
	for (i = 0; i < M; i++) {
		fixedProductId = pop();
		listInsert(fixedProductId);
	}
	pthread_barrier_wait(&phaseBarrier); // Step 4 Barrier
	// Step 4 check
	if(myId == 0) {
		int sizeFound;
		sizeFound = listSizeCheck();
		printf("List size check (expected: %d, found: %d)\n", N * N / 3, sizeFound);
	}
}



int main(int argc, char *argv[]) {
	
	int i;
	
	if (argc != 2 || atoi(argv[1]) % 3 != 0 || atoi(argv[1]) < 3) {
		printf("Usage: ./prj1 <N > 0 and can be divided by 3>\n");
		return 0;
	}
	
	// Read user parameters
	N = atoi(argv[1]);
	M = N / 3;
	
	// Initialize structures and their locks
	initializeList(N);
	initializeHashTables(N, M);
	// Stack does not need initialization, a pointer Top is enough, see .h file
	
	// Initialize threads and barriers
	pthread_t myThreads[N];
	pthread_barrier_init(&phaseBarrier, NULL, N);
	
	// Make threads work
	for(i = 0; i < N; i++) {
		struct args * myArgs = malloc(sizeof(struct args));
		myArgs->id = i;
		pthread_create(&(myThreads[i]), NULL, threadFunction, myArgs);	
	}
	
	// Wait for threads to finish
	for(i = 0; i < N; i++)   
		pthread_join((myThreads[i]), NULL);
	
	// Release barrier
	pthread_barrier_destroy(&phaseBarrier);
	
}