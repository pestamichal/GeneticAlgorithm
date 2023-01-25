#include <random>
#include "CIndividual.h"

CIndividual::CIndividual(int iSize) {

    uniform_int_distribution<int> dist(0, 1);
    random_device rd;
    mt19937 gen(rd());

    for(int i = 0; i < iSize; i++){
        v_genotype.push_back(dist(gen));
    }
}

CIndividual::CIndividual(vector<int>& vGenotype) {
    v_genotype = vGenotype;
}

int CIndividual::iCountFitness(const vector<int>& vValues, const vector<int>& vWeights, int iCapacity) {
    int i_fitness = 0;
    int i_weight = 0;
    for(int i = 0; i < v_genotype.size();i++){
        i_fitness += vValues.at(i)*v_genotype.at(i);
        i_weight += vWeights.at(i)*v_genotype.at(i);
    }
    if(i_weight <= iCapacity) return i_fitness;
    return 0;
}

void CIndividual::vMutate(float fMutProb) {
    uniform_real_distribution<> dist(0, 1);
    random_device rd;
    mt19937 gen(rd());

    for(int i = 0; i < v_genotype.size(); i++){
        float fMutate = dist(gen);
        if(fMutate < fMutProb){
         if(v_genotype.at(i) == 1) v_genotype.at(i) = 0;
         else v_genotype.at(i) = 1;
        }
    }
}

vector<CIndividual> CIndividual::vecCrossbreed(CIndividual &cOther) {
    vector<int> v_first_child_genotype, v_second_child_genotype;
    //random generator
    uniform_int_distribution<int> iPivotRange(1, v_genotype.size() - 1);
    random_device rd;
    mt19937 gen(rd());
    int i_pivot = iPivotRange(gen);
    //random generator

    for(int i = 0;i < i_pivot;i++){
        v_first_child_genotype.push_back(v_genotype.at(i));
        v_second_child_genotype.push_back(cOther.v_genotype.at(i));
    }

    for(int i = i_pivot; i < v_genotype.size();i++){
        v_first_child_genotype.push_back(cOther.v_genotype.at(i));
        v_second_child_genotype.push_back(v_genotype.at(i));
    }
    vector<CIndividual> v_res;
    CIndividual c_first_child(v_first_child_genotype);
    CIndividual c_second_child(v_second_child_genotype);
    v_res.push_back(c_first_child);
    v_res.push_back(c_second_child);
    return std::move(v_res);
}