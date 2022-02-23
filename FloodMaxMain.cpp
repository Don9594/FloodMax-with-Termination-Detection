#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

int main ()
{
    std::ifstream ifs;
    ifs.open("inputdata.txt");
    std::map<int, std::vector<int> > neighborsMap; // thread # -> vector of neighbors' UID
    int totalNumberOfThreads;
    std::vector<int> all_UIDs;

    // getting total number of threads
    {
        std::string line;
        std::getline(ifs, line);
        std::stringstream ss(line);
        ss >> totalNumberOfThreads;
        std::cout << "n: " << totalNumberOfThreads << std::endl;
    }
    // getting line of unique UIDs
    {
        std::string line;
        std::getline(ifs, line);
        std::stringstream ss(line);
        while(ss.good())
        {
            int temp_UID;
            ss >> temp_UID;
            all_UIDs.push_back(temp_UID);
        }
    }
    // getting line of each thread's neighbors
    {
        int currentThreadID = 0;
        do
        {
            std::string line;
            std::getline(ifs, line);
            std::stringstream ss(line);
            std::vector<int> myNeighbors;
            while(ss.good())
            {
                int temp_UID = -1;
                ss >> temp_UID;
                if (temp_UID == -1)
                    continue;
                myNeighbors.push_back(temp_UID);
            }
            neighborsMap.insert(std::pair<int, std::vector<int> >(currentThreadID, myNeighbors));
            currentThreadID++;
            ss.clear();
            
        }
        while (ifs.good());
    }


    // output
    std::cout << "UIDs" << std::endl;
    for (int it: all_UIDs)
    {
        std::cout << it << " ";
    }
    std::cout<< std::endl;
    for (auto it=neighborsMap.begin(); it != neighborsMap.end(); it++)
    {
        std::cout << "Thread # " << it->first << std::endl;
        for (int num: it->second)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    
    ifs.close();

    return 0;
}