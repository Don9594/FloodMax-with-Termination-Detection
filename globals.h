#ifndef GLOBALS
#define GLOBALS
//#include "semaphore.h"
#include<condition_variable>
#include "pthread.h"
//#include<mutex>

bool one;
bool two;
int round;
int diam_rounds;
int num_processes_completed_round;
int new_round;
//std::condition_variable cv_process_completed;
pthread_cond_t cond_process_completed;
pthread_mutex_t lock_process_completed;
//pthread_mutex_t master_completed_lock;
pthread_mutex_t lock_round_completed;

//lock to change round variable value

#endif