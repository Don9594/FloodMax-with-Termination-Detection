#ifndef master_thread
#define master_thread
#include <vector>


struct {
    int num_child_threads;
    std::vector<int> UID;
    std::vector<std::vector<int> > neighbor_UIDS;
}master;

#endif