#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>

int slave(int rank, int comm_sz);

int main(int argc, char **argv) 
{
  int rank, comm_sz, r_status;
  
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  if (rank != 0) {
    printf("Process %d out of %d processes executing.\n", rank, comm_sz);
    r_status = slave(rank, comm_sz); 
  }
 
  else {
    printf("Master process reporting.\n", rank, comm_sz);
    // master(comm_sz);   // to implement
    r_status = slave(rank, comm_sz);
  }
 
  printf("Process %d reports status: %d\n", rank, r_status);
  if (errno)
    perror("pre-finalize");
  if (MPI_Finalize() != 0) {
      perror("?");
  }
  
  return 0;
}

int slave(int rank, int comm_sz) { 
  static int i = 0;
  i++;
  char exec[64];
  sprintf(exec, "Rscript ana3.R krig_r%d_%d.rda > log%d.txt 2>&1", rank, i, rank);
  return system(exec);
}

  
