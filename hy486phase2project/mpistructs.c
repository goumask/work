#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define STRUCT_SIZE 2
#define MESSAGE_SIZE 12

struct record {
    int id;
    char message[MESSAGE_SIZE];
};

int main(int argc, char *argv[]) {
    
    int rank, world_size, i;
	/** MPI Initialisation **/
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    struct record dummy_record;

    // Calculate byte displacements for each block in struct
    MPI_Aint displacements[STRUCT_SIZE];
    MPI_Aint base_address;
    MPI_Get_address(&dummy_record, &base_address);
    MPI_Get_address(&dummy_record.id, &displacements[0]);
    MPI_Get_address(&dummy_record.message[0], &displacements[1]);
    displacements[0] = MPI_Aint_diff(displacements[0], base_address);
    displacements[1] = MPI_Aint_diff(displacements[1], base_address);

    // length of each field in struct
    int block_lengths[2] = {1, MESSAGE_SIZE};

    MPI_Datatype types[STRUCT_SIZE] = {MPI_INT, MPI_CHAR};

    // create struct
    MPI_Datatype RECORD_TYPE;
    MPI_Type_struct(STRUCT_SIZE, block_lengths, displacements, types, &RECORD_TYPE);
    MPI_Type_commit(&RECORD_TYPE);

    if(rank == 0) {
        // Coordinator
		printf("[rank: %d] Coordinator started\n", rank);
        for(i = 0; i < world_size; i++) {
			if(i == rank) continue;
            struct record senders_record;
            senders_record.id = i;
            strncpy(senders_record.message, "Hello World", 11);
            senders_record.message[12] = '\0';

            MPI_Send(&senders_record, 1, RECORD_TYPE, i, 0, MPI_COMM_WORLD);
        }
    }
    else {
		// Peers
		printf("[rank: %d] Peer started\n", rank);

        struct record rcvd_record;
		MPI_Recv(&rcvd_record, 1, RECORD_TYPE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		
		printf("[rank: %d] Peer received message: %s with id %d from %d\n", rank, rcvd_record.message, rcvd_record.id, 0);
	}

    // MPI_Type_free(&RECORD_TYPE);
	MPI_Finalize();

}