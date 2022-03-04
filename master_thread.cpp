#include"master_thread.h"
#include<iostream>
#include<unistd.h>
#include"process_thread.cpp"
#include<pthread.h>
#include"globals.h"
#include<condition_variable>
#ifndef master_thread_route
#define master_thread_route

using namespace std;

void * master_thread_routine(void * arg)
{
    one=false;
    two=false;
    round=0;
    int calculated_dfs_E=3;
    diam_rounds=calculated_dfs_E;
    struct master_info *ptr = (struct master_info *)arg;

    //cout << ptr->process_threads[0].UID <<endl;
    int numthreads = ptr->num_child_threads;
    pthread_t child_threads[numthreads];
    for(int i=0; i<numthreads;i++){
        int err=pthread_create(&child_threads[i],NULL,&process_thread_routine,&ptr->process_threads[i]);
        if (err){
            cout << "Thread creation failed : " << strerror(err);
            exit(1);
        }  
        else
            ;//cout << "Child Thread Created with ID : " <<child_threads[i] << endl;
    }

    
    pthread_mutex_init(&lock_round_completed,NULL);
    pthread_mutex_init(&lock_process_completed,NULL);
   
    
   
    while(round!=diam_rounds){

        pthread_mutex_lock(&lock_process_completed);
        one=true; two=false; 
        cout <<  "top round " << round <<endl;
        pthread_mutex_unlock(&lock_process_completed);

        while(num_processes_completed_round!=ptr->num_child_threads);
        
        
        pthread_mutex_lock(&lock_round_completed);
        //cout << round <<endl;
        num_processes_completed_round=0;
        round=round+1;
        cout << "inside round"<<round << endl;
        one=false; two=true;
        pthread_mutex_unlock(&lock_round_completed);

        // pthread_mutex_lock(&lock_process_completed);
        // pthread_cond_broadcast(&cond_process_completed);
        // pthread_mutex_unlock(&lock_process_completed);

        
    }

    cout<< "master got out of while loop" << endl;

    //wait for n threads to finish sending message

    //let threads read messages

    //wait for threads to finish reading
    int err;
    for(int i=0; i<numthreads;i++){
        err=pthread_join(child_threads[i],NULL);
    }
    
    return NULL;
}

#endif