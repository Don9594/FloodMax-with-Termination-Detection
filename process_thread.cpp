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

    ///////////
    while(1){

        //Floodmax Algorithm with Termination detection
        
        //send message
        pthread_mutex_lock(&lock_msgmap);
        for(int i=0; i<num_nbrs;i++){
            //send message type based on what to send
            msg.type=msg_t_nbrs[ptr->neighbor_UIDS[i]];
            msg.max_uid=local_max_uid;
            messagemap[ptr->neighbor_UIDS[i]].push_back(msg);
        }
        pthread_mutex_unlock(&lock_msgmap);


        //wait 
        while(1){
            pthread_mutex_lock(&lock_msgmap);
            if(messagemap[my_uid].size()==num_nbrs){
                break;
            }
            else{
                pthread_mutex_unlock(&lock_msgmap);
            }
        }
        pthread_mutex_unlock(&lock_msgmap);

        //msg: 0 search | 1 reject | 2 accept | 3 done | 4 terminate
        //read msgs
        pthread_mutex_lock(&lock_msgmap);
        for(int i=0; i<num_nbrs;i++){
            //looking message
            if(messagemap[my_uid][i].type==0){
                if(messagemap[my_uid][i].max_uid>local_max_uid){
                    
                    //set type to send

                    //set previous parent msg for next round to reject
                    if(parent!=my_uid) msg_t_nbrs[parent]=1;

                    parent=messagemap[my_uid][i].sender_uid;
                    
                    msg_t_nbrs[parent]=2;
                    local_max_uid=messagemap[my_uid][i].max_uid;
                    std::stringstream msg2;
                    msg2 << my_uid << " recieved id larger than local max: " << local_max_uid <<endl;
                    cout << msg2.str();
                    int j=0;
                    while(j<children.size()){
                        if(children[j]==parent){
                            children.erase(children.begin() + j);
                        }
                        j++;
                    }

                }
                else{
                    int x=messagemap[my_uid][i].sender_uid;
                    msg_t_nbrs[x]=1;
                }
            }//got a reject message
            else if(messagemap[my_uid][i].type==1){
                std::stringstream msg3;
                msg3 << my_uid <<"with max id " <<local_max_uid <<" got a reject message from " << messagemap[my_uid][i].sender_uid <<" with sender max: "<<messagemap[my_uid][i].max_uid<<"\n ";
                cout << msg3.str();
                if(local_max_uid== messagemap[my_uid][i].max_uid){
                    reject_msgs+=1;
                }
                int x=messagemap[my_uid][i].sender_uid;
                msg_t_nbrs[x]=0;
            }//got a accept message
            else if(messagemap[my_uid][i].type==2){
                std::stringstream msg4;
                msg4 << my_uid <<"with max id " <<local_max_uid << "got a accept message"<<messagemap[my_uid][i].sender_uid <<" with sender max: "<<messagemap[my_uid][i].max_uid<<"\n ";
                cout << msg4.str();
                //add to children
                int x=messagemap[my_uid][i].sender_uid;
                msg_t_nbrs[x]=0;
                children.push_back(x);
                
            }
            //got a done message
            else if(messagemap[my_uid][i].type==3){
                std::stringstream msg5;
                msg5 << my_uid <<"with max id " <<local_max_uid <<"got a done message from "<<messagemap[my_uid][i].sender_uid<<" with sender max: "<<messagemap[my_uid][i].max_uid <<"\n ";
                cout << msg5.str();
                done_msgs+=1;
                int x=messagemap[my_uid][i].sender_uid;
                msg_t_nbrs[x]=0;

            }
            //got a terminate message
            else if(messagemap[my_uid][i].type==4){
                //forward it and then terminate
                std::stringstream msg6;
                msg6 << my_uid <<"got a terminate message\n ";
                cout << msg6.str();
                terminate=true;
                break;
                
            }
            else{
                cout << "error. type was wrong" <<endl;
            }
        }
        pthread_mutex_unlock(&lock_msgmap);

        //handle i am done case;
        if(!terminate){

            pthread_mutex_lock(&lock_msgmap);
            if(reject_msgs+done_msgs==num_nbrs){
                if(my_uid==local_max_uid){
                    pthread_mutex_lock(&lock2);
                    terminate_variable++;
                    pthread_mutex_unlock(&lock2);
                    terminate=true;
                    for(int i=0; i<num_nbrs;i++){
                        int x=messagemap[my_uid][i].sender_uid;
                        msg_t_nbrs[x]=4;

                    }
                    std::stringstream msg10;
                    msg10 << my_uid <<" will send terminate msgs \n";
                    cout << msg10.str();
                }
            else{
                for(int i=0; i<num_nbrs;i++){
                    int x=messagemap[my_uid][i].sender_uid;
                    msg_t_nbrs[x]=3;
                }
                std::stringstream msg;
                msg << my_uid <<" will send i am done msgs  \n";
                cout << msg.str();
            }
            }
            pthread_mutex_unlock(&lock_msgmap);
        }


        

        //empty my vector
        pthread_mutex_lock(&lock_msgmap);
        messagemap[my_uid].clear();
        pthread_mutex_unlock(&lock_msgmap);


     
        
        //code below is just to complete round
        //cout << "child before lock" << endl;
        pthread_mutex_lock(&lock1);
        //cout << "chiild acquired lock " <<endl;
        num_processes_completed_round++;
        std::stringstream msg1;
        msg1 <<"child incremented : " << num_processes_completed_round <<'\n';
        cout << msg1.str();
        while(1){
            //cout << "child entered while loop " <<endl;
            pthread_cond_wait(&cv,&lock1);
            //cout <<"broadcast worked;" <<endl;
            break;
        }
        pthread_mutex_unlock(&lock1);

        pthread_mutex_lock(&lock_msgmap);
        if(terminate){
            for(int i=0; i<num_nbrs;i++){
                //send message type based on what to send
                int x=messagemap[my_uid][i].sender_uid;
                msg_t_nbrs[x]=4;
                msg.type=4;
                msg.max_uid=local_max_uid;
                messagemap[ptr->neighbor_UIDS[i]].push_back(msg);
            }
        }
        pthread_mutex_unlock(&lock_msgmap);
        done_msgs=0;
        reject_msgs=0;


        if(terminate){
            pthread_mutex_lock(&lock2);
            terminate_variable++;
            finish_threads=finish_threads+1;
            pthread_mutex_unlock(&lock2);
           break;
        }

    }
    std::cout << "thread exiting" <<std::endl;
    return NULL;
}
