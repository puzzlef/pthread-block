#pragma once
#define BUILD  0  // 5 == BUILD_TRACE
#define OPENMP 1
#ifdef ENABLE_MPI
#define MPI    1
#endif

#ifndef MAX_THREADS
#define MAX_THREADS 32
#endif

#include "_main.hxx"
