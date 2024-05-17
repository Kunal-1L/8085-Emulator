#include<string>
#include<map>
#include<vector>
#include<unordered_map>
using namespace std;

#ifndef FETCH_H
#define FETCH_H

class Fetch{
    public:
        static void fetchingFunctions(string startingAddress, map<string,vector<string>>& instructionMap, map<string,string>& directMap, unordered_map<string,string>& registers, vector<int>& flags);
};

#endif