#include "master_thread.h"
#include<iostream>
#include"globals.h"
#include<pthread.h>



using namespace std;

void *process_thread_routine(void* arg){
    struct thread_info *ptr = (struct thread_info *)arg;
    int max_uid= ptr->UID;

    while(1){
        cout << "child before lock" << endl;
        pthread_mutex_lock(&lock1);
        cout << "chiild acquired lock " <<endl;
        num_processes_completed_round++;
        std::stringstream msg;
        msg <<"child incremented : " << num_processes_completed_round <<'\n';
        cout << msg.str();
        while(1){
            cout << "child entered while loop " <<endl;
            pthread_cond_wait(&cv,&lock1);
            cout <<"broadcast worked;" <<endl;
            break;
        }
        pthread_mutex_unlock(&lock1);



        pthread_mutex_lock(&lock2);
        if (terminate_variable==false){
            pthread_mutex_unlock(&lock2);
            break;
        }
        pthread_mutex_unlock(&lock2);
    }
    std::cout << "thread exiting" <<std::endl;
    return NULL;
}

    //send message to neighbours


    //spin wait foe message queue


    //process messages //find max, select message type to send

    //if type 0 check for max id 

    //if type 1 it is a return 
