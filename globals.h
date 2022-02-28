#ifndef GLOBALS
#define GLOBALS
//#include "semaphore.h"
#include "pthread.h"

int round;
int num_processes_completed_round;
int new_round;
pthread_mutex_t child_completed_lock;
pthread_mutex_t main_completedt_lock;
pthread_mutex_t round_lock;
pthread_mutex_t queue_lock;
#endif