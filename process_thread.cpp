#include "master_thread.h"
#include<iostream>
#include"globals.h"
#include<pthread.h>
#include"message.h"
#include<vector>
//messagemap;

using namespace std;

void *process_thread_routine(void* arg){
    struct thread_info *ptr = (struct thread_info *)arg;
    int local_max_uid= ptr->UID;
    int my_uid=ptr->UID;
    int num_nbrs = ptr->neighbor_UIDS.size();
    struct message msg;
    int reject_msgs=0;
    int done_msgs=0;
    int done_msgs=0;
    int parent=my_uid;
    bool terminate=false;
    map<int,int> msg_t_nbrs;
    vector<int> children;
    for(int i=0; i<num_nbrs; i++){
        msg_t_nbrs[ptr->neighbor_UIDS[i]]=0;
    }

    msg.sender_uid =my_uid;
    msg.type=0;
    msg.max_uid=local_max_uid;
    while(1){

        //Floodmax Algorithm with Termination detection
        
        //send message
        pthread_mutex_lock(&lock_msgmap);
        for(int i=0; i<num_nbrs;i++){
            //send message type based on what to send
            msg.type=msg_t_nbrs[ptr->neighbor_UIDS[i]];
            messagemap[ptr->neighbor_UIDS[i]].push_back(msg);
        }
        pthread_mutex_unlock(&lock_msgmap);


        //wait 
        while(messagemap[my_uid].size()!=num_nbrs);

        //msg: 0 search | 1 reject | 2 accept | 3 done | 4 terminate
        //read msgs
        pthread_mutex_lock(&lock_msgmap);
        for(int i=0; i<num_nbrs;i++){
            //looking message
            if(messagemap[my_uid][i].type==0){
                if(messagemap[my_uid][i].max_uid>local_max_uid){
                    //set type to send
                    if(parent!=my_uid) msg_t_nbrs[parent]=1;
                    parent=messagemap[my_uid][i].sender_uid;
                    msg_t_nbrs[parent]=2;
                    local_max_uid=messagemap[my_uid][i].max_uid;
                }
                else{
                    int x=messagemap[my_uid][i].sender_uid;
                    msg_t_nbrs[x]=1;
                }
            }
            //got a reject message
            else if(messagemap[my_uid][i].type==1){
                if(local_max_uid>= messagemap[my_uid][i].max_uid){
                    reject_msgs+=1;
                }
                int x=messagemap[my_uid][i].sender_uid;
                msg_t_nbrs[x]=0;
            }
            //got a accept message
            else if(messagemap[my_uid][i].type==2){
                //add to children
                int x=messagemap[my_uid][i].sender_uid;
                msg_t_nbrs[x]=0;
                children.push_back(x);
                
            }
            //got a done message
            else if(messagemap[my_uid][i].type==3){
                done_msgs+=1;
            }
            //got a terminate message
            else if(messagemap[my_uid][i].type==4){
                //forward it and then terminate
                int x=messagemap[my_uid][i].sender_uid;
                msg_t_nbrs[x]=4;
                
            }
            else{
                cout << "error. type was wrong" <<endl;
            }
            //
        }
        pthread_mutex_unlock(&lock_msgmap);

        pthread_mutex_lock(&lock_msgmap);
        if(terminate){
            for(int i=0; i<num_nbrs;i++){
                //send message type based on what to send
                int x=messagemap[my_uid][i].sender_uid;
                msg_t_nbrs[x]=4;
                msg.type=4;
                messagemap[ptr->neighbor_UIDS[i]].push_back(msg);
            }
            break;
        }
        pthread_mutex_unlock(&lock_msgmap);

     

        
























        //code below is just to complete round
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
