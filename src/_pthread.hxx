#pragma once
#include <cstddef>
#include <utility>
#include <functional>
#include <algorithm>
#include <vector>
#include <pthread.h>

using std::function;
using std::pair;
using std::vector;




// PARALLEL BLOCK
// --------------

inline void* parallelBlockHandlerPthread(void *data) {
  using DATA = pair<int, function<void(int)>>;
  const DATA& x = *((DATA*) data);
  LOG("parallelBlockHandlerPthread()\n");
  x.second(x.first);
  return nullptr;
}


template <class F>
inline vector<pthread_t> parallelBlockCreatePthread(int numThreads, F fn) {
  using  DATA = pair<int, function<void(int)>>;
  vector<DATA>      threadData(numThreads);
  vector<pthread_t> threads(numThreads);
  for (int i=0; i<numThreads; ++i) {
    threadData[i] = make_pair(i, function<void(int)>(fn));
    pthread_create(&threads[i], nullptr, parallelBlockHandlerPthread, &threadData[i]);
  }
  return threads;
}


inline void parallelBlockJoinPthread(const vector<pthread_t>& threads) {
  for (int i=0; i<threads.size(); ++i)
    pthread_join(threads[i], nullptr);
}


template <class F>
inline void parallelBlockPthread(int numThreads, F fn) {
  auto threads = parallelBlockCreatePthread(numThreads, fn);
  parallelBlockJoinPthread(threads);
}




// SIGNALLING
// ----------

inline void parallelBlockWaitPthread(pthread_cond_t& cond, pthread_mutex_t& mutex) {
  pthread_mutex_lock(&mutex);
  pthread_cond_wait(&cond, &mutex);
  pthread_mutex_unlock(&mutex);
}


inline void parallelBlockSignalPthread(pthread_cond_t& cond, pthread_mutex_t& mutex) {
  pthread_mutex_lock(&mutex);
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);
}


inline void parallelBlockBroadcastPthread(pthread_cond_t& cond, pthread_mutex_t& mutex) {
  pthread_mutex_lock(&mutex);
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&mutex);
}
