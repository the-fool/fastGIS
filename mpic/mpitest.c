#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

int slave(int rank, char* path);
char *timestamp();

int main(int argc, char **argv) 
{
  int rank, comm_sz, r_status;
  char* FGIS_PATH = getenv("FASTGIS_PATH");
  if (FGIS_PATH == NULL)
    printf("path is null\n");
  else
    printf("%s\n", FGIS_PATH);
  /* 
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  
  // slave(rank, FGIS_PATH);
 
  if (errno)
    perror("pre-finalize");
  if (MPI_Finalize() != 0) {
      perror("MPI_Finalize");
      }*/
  return 0;
}

int slave(int rank, char *path) { 
  static int i = 0;
  printf("in slave\n");
  int r_status;
  char exec[64];
  char *tstamp = timestamp();
  
  i++;
  printf("%sProc %d on iteration: %d\n\n", tstamp, rank, i);
  sprintf(exec, "Rscript %s/rscripts/rtest.R >> %s/logs/test%d.log 2>&1", path, path, rank);
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
