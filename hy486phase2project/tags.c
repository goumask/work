#include <stdio.h>
#include <stdlib.h>
#include <mpi.h> 
#include <stddef.h> 

#define INFO 0 
#define ERROR 1


int main(int argc, char *argv[]){

	int rank, world_size, i;
	/** MPI Initialisation **/
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;
	int dummy_int;
	
	if(rank == 0){
		// Coordinator
		printf("[rank: %d] Coordinator started\n", rank);
		
		for(i = 0; i< world_size/2; i++){
			if(i == rank) continue;
			MPI_Send(&dummy_int, 1, MPI_INT, i, INFO, MPI_COMM_WORLD);
		}
		for(i = world_size/2; i< world_size; i++){
			if(i == rank) continue;
			MPI_Send(&dummy_int, 1, MPI_INT, i, ERROR, MPI_COMM_WORLD);
		}
	}else{
		// Peers
		printf("[rank: %d] Peer started\n", rank);
		MPI_Recv(&dummy_int, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		if(status.MPI_TAG == INFO)
			printf("[rank: %d] Peer received message of type INFO from %d\n", rank, status.MPI_SOURCE);
		else if (status.MPI_TAG == ERROR)
			printf("[rank: %d] Peer received message of type ERROR from %d\n", rank, status.MPI_SOURCE);

	}
	MPI_Finalize();
}
