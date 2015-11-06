#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

int slave(int rank, int comm_sz);
char *timestamp();

int main(int argc, char **argv) 
{
  int rank, comm_sz, r_status;
  
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  
  // MPI_Errhandlerset(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

  if (argc != 2) {
    fprintf(stderr, "Usage: krig n_iter\n");
    exit(1);
  }
  int n = atoi(argv[1]);
  printf("Begin %d iterations of %d processes\n", n, comm_sz);
  int i;
  for (i = 0; i < n; i++) {   
    slave(rank, comm_sz);
  }
  
  if (errno)
    perror("pre-finalize");
  if (MPI_Finalize() != 0) {
      perror("MPI_Finalize");
  }

  return 0;
}

int slave(int rank, int comm_sz) { 
  static int i = 0;
  int r_status;
  char exec[64];
  char *tstamp = timestamp();
  
  i++;
  printf("%sProc %d on iteration: %d\n\n", tstamp, rank, i);
  sprintf(exec, "Rscript Ana2.R krig_r%d_%d.rda >> log%d.txt 2>&1", rank, i, rank);
  if ((r_status = system(exec)) != 0)
    printf("ERROR: Proc %d reports status: %d\n", rank, r_status);
  return r_status;
}

char *timestamp()
{
  static char tstamp[128];
  time_t ltime;
  ltime=time(NULL);
  sprintf(tstamp, "%s", asctime( localtime(&ltime) ) );
  return tstamp;
}
