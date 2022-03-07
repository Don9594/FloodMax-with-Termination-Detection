#ifndef GLOBALS
#define GLOBALS
//#include "semaphore.h"
#include "pthread.h"
//#include<mutex>

int terminate_variable;
int num_processes_completed_round;
int finish_threads;
pthread_mutex_t lock1;
pthread_mutex_t lock2;
pthread_cond_t cv;


pthread_mutex_t lock_msgmap;
//pthread_cond_t cond_process_completed;
//pthread_mutex_t lock_process_completed;
//pthread_mutex_t master_completed_lock;


//lock to change round variable value

#endif