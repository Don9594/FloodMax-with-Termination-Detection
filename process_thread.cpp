#include "master_thread.h"
#include<iostream>
#include"globals.h"
#include<pthread.h>


void *process_thread_routine(void* arg){
    struct thread_info *ptr = (struct thread_info *)arg;
    bool tmp = true;
    while(round!=diam_rounds){
        while(!one){

        }

        pthread_mutex_lock(&lock_process_completed);
        pthread_mutex_unlock(&lock_process_completed);

        //send message 

        //wait for messages to come from all neighbours
        pthread_mutex_lock(&lock_round_completed);
        num_processes_completed_round++;
        std::cout << "num_processes_completed_round" << num_processes_completed_round << std::endl;
        pthread_mutex_unlock(&lock_round_completed);
        //std::cout << "Round " << round << "UID " << ptr->UID <<std::endl;

        //check for messages 
        //pthread_mutex_lock(&lock_process_completed);
        while(!two){
           // pthread_cond_wait(&cond_process_completed,&lock_process_completed);
        }
        pthread_mutex_lock(&lock_round_completed);
        pthread_mutex_unlock(&lock_round_completed);
        
        //pthread_mutex_unlock(&lock_process_completed);  
            

        //std::unique_lock<std::mutex> lck (lock_process_completed);
        
        

    }
    // //FLoodMax Algorithm 
    // int max_id = ptr->UID;
    return NULL;
}

/*
thread 1:
  

thread2:
    pthread_mutex_lock(&mutex);
    do something that might make condition true 
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
*/