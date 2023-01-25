#include <iostream>
#include <vector>
using namespace std;

#ifndef MINI_PROJECT_CINDIVIDUAL_H
#define MINI_PROJECT_CINDIVIDUAL_H

class CIndividual {
public:
    CIndividual(int iSize);
    CIndividual(vector<int>& vGenotype);
    ~CIndividual() = default;
    int iCountFitness(const vector<int>& vValues, const vector<int>& vWeights, int iCapacity);
    vector<int>& vecGetGenotype(){ return v_genotype;}
    void vMutate(float fMutProb);
    vector<CIndividual> vecCrossbreed(CIndividual& cOther);
private:
    vector<int> v_genotype;
};




#endif //MINI_PROJECT_CINDIVIDUAL_H
