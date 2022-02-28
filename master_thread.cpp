#include"master_thread.h"
#include<iostream>
#include<unistd.h>
#include"process_thread.cpp"
#include<pthread.h>
#include"globals.h"
#ifndef master_thread_route
#define master_thread_route

using namespace std;

void * master_thread_routine(void * arg)
{
    round =0;
    int totalrounds =10;
    std::cout << "Thread Function :: Start" << std::endl;
    // Sleep for 2 seconds
    sleep(2);
    std::cout << "Thread Function :: End" << std::endl;
    //launch child threads 
    struct master_info *ptr = (struct master_info *)arg;

    cout << ptr->process_threads[0].UID <<endl;
    int numthreads = ptr->num_child_threads;
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

    
    pthread_mutex_init(&round_lock,NULL);

    pthread_mutex_lock(&round_lock);
    while(round!=totalrounds){
    pthread_mutex_unlock(&round_lock);
    //do things 

    pthread_mutex_lock(&round_lock);
    round++;
    pthread_mutex_unlock(&round_lock);
    }
    pthread_mutex_unlock(&round_lock);


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