#include<iostream>
#include<unistd.h>

void * master_thread_routine(void * arg)
{
    std::cout << "Thread Function :: Start" << std::endl;
    // Sleep for 2 seconds
    sleep(2);
    std::cout << "Thread Function :: End" << std::endl;
    //launch child threads 

    //for n rounds 
    //wait for n threads to finish sending message

    //let threads read messages

    //wait for threads to finish reading

    return NULL;
}