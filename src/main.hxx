#pragma once
#define BUILD  0  // 5 == BUILD_TRACE
#define OPENMP 1
#if ENABLED_MPI!=0
#define MPI    1
#endif

#ifndef MAX_THREADS
#define MAX_THREADS 32
#endif

#include "_main.hxx"
