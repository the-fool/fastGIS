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
  
   slave(rank, comm_sz);
 
  
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
  char *path = "/home/truble/fastGIS/rscripts/";

  i++;
  printf("%sProc %d on iteration: %d\n\n", tstamp, rank, i);
  sprintf(exec, "Rscript %srtest.R >> test%d.log 2>&1", path, rank, i, rank);
  if ((r_status = system(exec)) != 0)
    printf("ERROR: Proc %d reports status: %d\n", rank, r_status);
  else
    printf("SUCCESS at proc: %d\n", rank);
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
