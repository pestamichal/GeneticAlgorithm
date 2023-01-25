#ifndef MINI_PROJECT_CKNAPSACKPROBLEM_H
#define MINI_PROJECT_CKNAPSACKPROBLEM_H

#include "CProblem.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


class CKnapsackProblem : public CProblem {
public:
    CKnapsackProblem();
    ~CKnapsackProblem() override = default;
    vector<int>& GetValues() override{ return v_values;}
    vector<int>& GetWeights() override{ return v_weights;}
    int iGetCapacity() const override{ return i_capacity;}
    int iGetItemsNum() const override{ return i_items_number;}
    bool vInitialize(const string& sFilePath);
    bool bGetIsReady() const override {return b_is_ready;}
    int iCalcFitness(vector<int>& vGenotype);

private:
    bool bInvalidFile(ifstream& pfHandle);
    bool bOpenFile(ifstream& pfHandle, const string& sFileName);
    void vReadFile(ifstream& pfHandle);
    void vReset();
    void vPrintData();
    vector<int> v_values;
    vector<int> v_weights;
    int i_capacity;
    int i_items_number;
    bool b_is_ready;
};


#endif //MINI_PROJECT_CKNAPSACKPROBLEM_H
