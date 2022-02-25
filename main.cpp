#include <iostream>
#include<fstream>
#include <vector>
#include "master_thread.h"
#include<string>

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
    
    //process input file


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

void processfile(ifstream &input){
    //char* g;
    //input.getline(g,256);
    //int num_nodes; 
    //num_nodes=(int)input.get();
    //master.num_child_threads=num_nodes;
    //cout << "num nodes is " << g[0] << endl;
}