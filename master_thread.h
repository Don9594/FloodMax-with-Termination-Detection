#ifndef master_thread
#define master_thread
#include <vector>
//#include "master_thread.cpp"


struct thread_info{
    int UID;
    std::vector<int > neighbor_UIDS;
};

struct master_info{
    int num_child_threads;
    std::vector<struct thread_info> process_threads;
};

void* master_thread_routine(void * arg);

#endif