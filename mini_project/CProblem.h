

#ifndef MINI_PROJECT_CPROBLEM_H
#define MINI_PROJECT_CPROBLEM_H

#include <iostream>
#include <vector>
using namespace std;

class CProblem {
public:
    virtual ~CProblem() = default;
    virtual vector<int>& GetValues() = 0;
    virtual vector<int>& GetWeights() = 0;
    virtual int iGetCapacity() const = 0;
    virtual int iGetItemsNum() const = 0;
    virtual bool bGetIsReady() const = 0;
};


#endif //MINI_PROJECT_CPROBLEM_H
