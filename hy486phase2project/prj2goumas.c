// Kostas Goumas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h> 

// Orizoume ta tags
#define CONNECT 0
#define REGISTER 1
#define REGISTER_IN 2
#define REGISTER_OUT 3
#define TERMINATE 9

int main(int argc, char *argv[]) {

	int rank, world_size;
	char fileName[30];
	int NUM_SERVERS;
	FILE *fp;
	

	if (argc != 2) {
		printf("Wrong number of arguments\n");
		return 0;
	}
	
	// Read user parameters
	NUM_SERVERS = atoi(argv[1]);
	
	// Voithitikos kodikas gia na anoiksei ta sosta arxeia
	if (NUM_SERVERS == 2) {
		strcpy(fileName, "np20_servers4.txt");
	}
	else if (NUM_SERVERS == 3) {
		strcpy(fileName, "np45_servers9.txt");
	}
	else if (NUM_SERVERS == 4) {
		strcpy(fileName, "np65_servers16.txt");
		
	}
	else {
		printf("Non appropriate input file found\n");
		return 0;
	}
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;
	
	if(rank == 0) { // An eimai o coordinator
		//Anoigo kai diavazo to arxeio
		fp = fopen(fileName, "r");
		
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		
		https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
		while ((read = getline(&line, &len, fp)) != -1) {
			//printf("Retrieved line of length %zu:\n", read);
			//printf("%s", line);
			// https://stackoverflow.com/questions/18421310/reading-a-file-line-by-line-and-splitting-the-string-into-tokens-in-c
			const char* eventType = strtok(line, " ");
			//printf("%s\n", eventType);
			// Event of type CONNECT
			if (strcmp(eventType, "CONNECT") == 0) {
				//printf("%s\n", eventType);
				const char* processToSendInfoStr = strtok(NULL, " ");
				//printf("%s\n", processToSendInfoStr);
				int processToSendInfo = atoi(processToSendInfoStr);
				const char* neighborOfProcessStr = strtok(NULL, "\n");
				//printf("%s\n", neighborOfProcessStr);
				int neighborOfProcess = atoi(neighborOfProcessStr);
				//printf("%d %d\n", processToSendInfo, neighborOfProcess);
				// Proetoimasia Connect message apo coordinator pros client
				char connectMessage[20];
				//strcpy(connectMessage, "CONNECT");
				//strcat(connectMessage, " ");
				//strcat(connectMessage, neighborOfProcessStr);
				//printf("%s\n", connectMessage);
				// Apostoli Connect message apo coordinator pros client
				MPI_Send(&neighborOfProcess, 1, MPI_INT, processToSendInfo, CONNECT, MPI_COMM_WORLD);
			}
			// REGISTER
			else if (strcmp(eventType, "REGISTER") == 0) {
				
				// Where to send the info
				const char* processToSendInfoStr = strtok(NULL, " ");
				int processToSendInfo = atoi(processToSendInfoStr);
				// Register in or out
				const char* inOrOut = strtok(NULL, " ");
				// Date missing
				//const char* dateInfo = strtok(NULL, "\n");
				int dummyInt;
				if (strcmp(inOrOut, "IN") == 0) { // Case register in
					MPI_Send(&dummyInt, 1, MPI_INT, processToSendInfo, REGISTER_IN, MPI_COMM_WORLD);
				}
				else { // Case register out
					MPI_Send(&dummyInt, 1, MPI_INT, processToSendInfo, REGISTER_OUT, MPI_COMM_WORLD);
				}
			}
			
			
		}
		
		// To arxeio teleiose terminate everything!
		fclose(fp);
		int i;
		for (i = 1; i < world_size; i++) {
			// Stelno terminate minima se oles tis diergasies tou world
			int dummy_int;
			MPI_Send(&dummy_int, 1, MPI_INT, i, TERMINATE, MPI_COMM_WORLD);
		}
	}
	else {
		//##################
		// An eimai server
		//##################
		if (rank <= NUM_SERVERS * NUM_SERVERS) {
			int intIReceived;
			int end = 0;
			while(end == 0) { // Mexri na laveis terminate apo ton coordinator sinexise na perimeneis na laveis kati
				MPI_Recv(&intIReceived, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				// REGISTER
				if(status.MPI_TAG == REGISTER_IN || status.MPI_TAG == REGISTER_OUT) {	// An lavo REGISTER minima
					if (status.MPI_TAG == REGISTER_IN) {
						printf("[rank: %d] Server received message of type REGISTER IN from %d\n", rank, status.MPI_SOURCE);
						// Process request...
					}
					else {
						printf("[rank: %d] Server received message of type REGISTER OUT from %d\n", rank, status.MPI_SOURCE);
						// Process request...
					}
				}
				// TERMINATE
				else if(status.MPI_TAG == TERMINATE) {	// An lavo connect minima
					printf("[rank: %d] Server received message of type TERMINATE from %d.\n", rank, status.MPI_SOURCE);
					end = 1;
				}
			}
		}
			
		
		//##################
		// An eimai client
		//##################
		else if (rank > NUM_SERVERS * NUM_SERVERS) {
			int intIReceived, dummyInt;
			int end = 0;
			int numberOfRequests = 0;
			while(end == 0) { // Mexri na laveis terminate apo ton coordinator sinexise na perimeneis na laveis kati
				MPI_Recv(&intIReceived, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				if(status.MPI_TAG == CONNECT) {	// An lavo connect minima
					printf("[rank: %d] Client received message of type CONNECT from %d. My neighbor: %d\n", rank, status.MPI_SOURCE, intIReceived);
				}
				else if(status.MPI_TAG == REGISTER_IN || status.MPI_TAG == REGISTER_OUT) {	// An lavo REGISTER minima
					numberOfRequests++;
					if (status.MPI_TAG == REGISTER_IN) {
						printf("[rank: %d] Client received message of type REGISTER IN from %d\n", rank, status.MPI_SOURCE);
						// Send request to appropriate server
						MPI_Send(&dummyInt, 1, MPI_INT, numberOfRequests % NUM_SERVERS, REGISTER_IN, MPI_COMM_WORLD);
					}
					else {
						printf("[rank: %d] Client received message of type REGISTER OUT from %d\n", rank, status.MPI_SOURCE);
						// Send request to appropriate server
						MPI_Send(&dummyInt, 1, MPI_INT, numberOfRequests % NUM_SERVERS, REGISTER_OUT, MPI_COMM_WORLD);
					}
				}
				else if(status.MPI_TAG == TERMINATE) {	// An lavo TERMINATE minima
					printf("[rank: %d] Client received message of type TERMINATE from %d.\n", rank, status.MPI_SOURCE);
					end = 1;
				}
			}
		}
	}
	
	MPI_Finalize();
	
}