

#include <fstream>
#include "CKnapsackProblem.h"

CKnapsackProblem::CKnapsackProblem() {
   i_capacity = 0;
   i_items_number = 0;
   b_is_ready = false;
}

bool CKnapsackProblem::vInitialize(const string& sFilePath) {
    ifstream f_file;
    vReset();
    if(bOpenFile(f_file, sFilePath)){
        f_file>>i_items_number>>i_capacity;
        vReadFile(f_file);
        f_file.close();
        if(bInvalidFile(f_file)) {
            cout<<"Invalid file."<<endl;
            vReset();
            return false;
        }else{
            cout<<"Knapsack problem ready."<<endl;
            b_is_ready = true;
            vPrintData();
            return true;
        }
    }else{
        cout<<"Opening file failed."<<endl;
        vReset();
        return false;
    }
}

void CKnapsackProblem::vReadFile(ifstream& pfHandle){
    int i_temp;
    int ii = 0;
    while(pfHandle >> i_temp && ii < i_items_number){
        v_values.push_back(i_temp);
        pfHandle >> i_temp;
        v_weights.push_back(i_temp);
        ii++;
    }
}

bool CKnapsackProblem::bOpenFile(ifstream& pfHandle,const string& sFileName) {
    pfHandle.open(sFileName);
    return (pfHandle.good());
}

bool CKnapsackProblem::bInvalidFile(ifstream& pfHandle) {
    return (pfHandle.fail() && !pfHandle.eof() || v_values.size() != v_weights.size() || i_items_number <= 0 || i_capacity <= 0);
}

void CKnapsackProblem::vReset() {
    v_values.clear();
    v_weights.clear();
    i_capacity = 0;
    i_items_number = 0;
    b_is_ready = false;
}

int CKnapsackProblem::iCalcFitness(vector<int> &vGenotype) {
    int i_value = 0;
    int i_weight = 0;
    for(int i = 0; i < vGenotype.size();i++){
        if(vGenotype.at(i) == 1){
            i_value += v_values.at(i);
            i_weight += v_weights.at(i);
        }
    }
    if(i_weight <= i_capacity) return i_value;
    else return 0;
}

void CKnapsackProblem::vPrintData() {
    cout<<"Values: "<<endl;
    for(int v_value : v_values){
        cout<<v_value<<" ";
    }
    cout<<endl;
    cout<<"Weights: "<<endl;
    for(int v_weight : v_weights){
        cout<<v_weight<<" ";
    }
    cout<<endl;
    cout<<"Capacity: "<<endl;
    cout<<i_capacity<<endl;
}
