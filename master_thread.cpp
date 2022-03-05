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
    num_processes_completed_round=0;
    terminate_variable=true;
    int round=0;
    int diam_rounds=3;
    struct master_info *ptr = (struct master_info *)arg;
    pthread_cond_init(&cv,NULL);
    pthread_mutex_init(&lock1,NULL);
    pthread_mutex_init(&lock2,NULL);

    //cout << ptr->process_threads[0].UID <<endl;
    int numthreads = ptr->num_child_threads;
    cout << "numthreads: " << numthreads << endl;
    pthread_t child_threads[numthreads];
    for(int i=0; i<numthreads;i++){
        int err=pthread_create(&child_threads[i],NULL,&process_thread_routine,&ptr->process_threads[i]);
        if (err){
            cout << "Thread creation failed : " << strerror(err);
            exit(1);
        }  
        else
            cout << "Child Thread Created with ID : " <<child_threads[i] << endl;
    }

    
   
    while(round!=diam_rounds){
        cout << "entered main while loop before lock" <<endl;


        pthread_mutex_lock(&lock1);
        if(num_processes_completed_round==numthreads){
            num_processes_completed_round=0;
            round++;
            pthread_cond_broadcast(&cv);
            pthread_mutex_unlock(&lock1);
            cout<< "sent out broadcast" <<endl;
     
           
        }
        else{
            std::stringstream msg;
            msg << "main thread gives up lock:"<< num_processes_completed_round <<'\n';
            cout << msg.str();
            pthread_mutex_unlock(&lock1);

        }
    }



    pthread_mutex_lock(&lock2);
    terminate_variable=false;
    pthread_mutex_unlock(&lock2);

    int err;
    for(int i=0; i<numthreads;i++){
        err=pthread_join(child_threads[i],NULL);
    }
    
    return NULL;
}

#endif