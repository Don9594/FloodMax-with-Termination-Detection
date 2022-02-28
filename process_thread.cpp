#include "master_thread.h"
#include<iostream>
#include"globals.h"
void *process_thread_routine(void* arg){
    
    struct thread_info *ptr = (struct thread_info *)arg;
    std::cout << ptr->UID;

    //FLoodMax Algorithm 
    int max_id = ptr->UID;

    //send message to neighbors
    //sends one every round 

    return NULL;
}
