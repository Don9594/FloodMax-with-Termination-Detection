#ifndef message_h
#define message_h
#include<vector>
#include<map>

using namespace std;

//msg: 0 search | 1 reject | 2 accept | 3 done | 4 terminate

struct message{
    int type;
    int max_uid;
    int sender_uid;
};

map<int,vector<struct message> > messagemap;

#endif