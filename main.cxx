#include <iostream>
#include <cstdio>
#include "src/main.hxx"

using namespace std;




// MAIN
// ----

int main(int argc, char** argv) {
  #ifdef MPI
  char pname[MPI_MAX_PROCESSOR_NAME];
  int  PNAME = 0, p = 0, P = 0;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &P);
  MPI_Comm_rank(MPI_COMM_WORLD, &p);
  MPI_Get_processor_name(pname, &PNAME);
  if (p==0) LOG("COMM_SIZE=%d\n", P);
  LOG("PROCESSOR_NAME=%s\n", pname);
  #endif
  omp_set_num_threads(MAX_THREADS);
  LOG("OMP_NUM_THREADS=%d\n", omp_get_max_threads());
  int count = 0;
  parallelBlockPthread(MAX_THREADS, [&](int t) {
    count += t;
  });
  LOG("count=%d\n", count);
  return 0;
}
