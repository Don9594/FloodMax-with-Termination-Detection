#include <iostream>
#include<fstream>
#include <vector>
#include "master_thread.h"
#include<string>
#include<sstream>
using namespace std;

void openfile(string, ifstream &);

void processfile(ifstream &);

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

    //wait for master thread to finish 

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
   
    while (getline(iss, token, ' '))
    {
        master.UID.push_back(stoi(token));
    }

    master.neighbor_UIDS.resize(master.num_child_threads);
   
    for(int i=0; i<master.num_child_threads;i++){
        getline(inputfile,str);
        istringstream is(str);
        cout << str << endl;
    
        while (getline(is, token, ' '))
        {
            int x = stoi(token);
            master.neighbor_UIDS[i].push_back(master.UID[x-1]);
        }
    }

    for(int i =0; i<master.UID.size(); i++){
        cout << master.UID[i] <<endl;
    }

    for(int i =0; i<master.UID.size(); i++){
        cout << "UID is " << master.UID[i] << ". neighbors are : ";
        for (int j=0; j<master.neighbor_UIDS[i].size(); j++){
            cout << master.neighbor_UIDS[i][j] << " ";
        }
        cout <<endl;
    }



}