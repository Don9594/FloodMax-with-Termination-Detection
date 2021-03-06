#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<pthread.h>
//#include"master_thread.h"
#include"master_thread.cpp"
using namespace std;

void openfile(string, ifstream &);

void processfile(ifstream &);

master_info master;

int main(int argc, char *argv[]){
    
    
    ifstream inputfile;

    if(argc ==1){
        //run sample file "input.txt"
        cout<<"no argument passed in. default file will be used as input." <<endl;
        openfile("input.txt",inputfile);
        processfile(inputfile);  
    }
    else if(argc ==2){
        //run input file
        cout<<"argument "<< argv[1]<<" passed in." <<endl;
        openfile(argv[1],inputfile);
        processfile(inputfile);  
    }
    else{
        //throw error
        cout<<"Incorrect number of arguments passed in. Exiting..." <<endl;
        exit(1);
    }
    
    //process input file : done

    //launch master thread
    pthread_t master_thread1;

    int err=pthread_create(&master_thread1,NULL,&master_thread_routine,&master);

    if (err){
        cout << "Thread creation failedd: " ;
        exit(1);
    }  
    else
        //cout << "Thread Created with ID : " << master_thread1 << std::endl;
    

    //wait for master thread to finish
    err=pthread_join(master_thread1,NULL);

    //close files 
    inputfile.close();
    return 0;
}

void openfile(string filename,ifstream &infile ){
    infile.open(filename);
    //add protection
}

//try implementation with dynamic array later
//(consider whitespace character to count ill use getline)

//why I used >> instead of .get & .getline ? 
//ignore whitespace incase user entered whitespace
//disadvantage: manually get rid of newline 

void processfile(ifstream &inputfile){
    //store number of nodes in master variable one 

    //store child thread uids in vector 

    //store number of nodes
    string str;
    string token;
    getline(inputfile,str);
    master.num_child_threads=stoi(str);
    
    //store child thread info
    getline(inputfile,str);
    istringstream iss(str);

    master.process_threads.resize(master.num_child_threads);

    int k=0;
    while (getline(iss, token, ' '))
    {
        master.process_threads[k].UID=stoi(token);
        //cout  << k << master.process_threads[k].UID <<endl;
        ++k;
    }
    
    for(int i=0; i<master.num_child_threads;i++){
        getline(inputfile,str);
        istringstream is(str);
    
        while (getline(is, token, ' '))
        {
            int x = stoi(token);
            int sid = master.process_threads[x-1].UID;
            master.process_threads[i].neighbor_UIDS.push_back(sid);
        }
    }




}