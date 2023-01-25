

#ifndef MINI_PROJECT_CGENETICALGORITHM_H
#define MINI_PROJECT_CGENETICALGORITHM_H
#include <vector>
#include "CKnapsackProblem.h"
#include "CIndividual.h"
using namespace std;


class CGeneticAlgorithm {
public:
    CGeneticAlgorithm(int iPopSize, float fCrossProb, float fMutProb, int iIterations);
    ~CGeneticAlgorithm();
    bool bSetupAlgorithm(CProblem* pcProblem);
    vector<int> vecGetSolution(){return v_best_solution;}
    void vPrintSolution();
    bool vRun();
private:
    void vGenerateRandomPop();
    void vCalcFitness();
    void vCalcBestSolution();
    void vCross();
    void vChooseParents(int& id_1, int& id_2);
    void vMutate();
    bool bCrossbreed() const;
    void vRunAlgorithm();
    void vClearPrevSolution();
    bool bValidate(int iPopSize, float fCrossProb, float fMutProb, int iIterations);
    void vCreate(int iPopSize, float fCrossProb, float fMutProb, int iIterations);
    int i_pop_size;
    float f_cross_prob;
    float f_mut_prob;
    int i_iterations;
    int i_best_solution_fitness;
    bool b_ready;
    vector<int> v_best_solution;
    vector<int> v_pop_fitness;
    vector<CIndividual>* pv_curr_pop;
    vector<CIndividual>* pv_new_pop;
    CProblem* pc_problem;
};


#endif //MINI_PROJECT_CGENETICALGORITHM_H
