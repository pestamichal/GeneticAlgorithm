#include "CGeneticAlgorithm.h"
#include <random>

using namespace std;

const int I_DEFAULT_POP_SIZE = 10;
const float F_DEFAULT_CROSS_PROB = 0.6;
const float F_DEFAULT_MUT_PROB = 0.2;
const int I_DEFAULT_ITERATIONS = 100;

CGeneticAlgorithm::CGeneticAlgorithm(int iPopSize, float fCrossProb, float fMutProb, int iIterations) {
    if(bValidate(iPopSize, fCrossProb, fMutProb, iIterations)){
        vCreate(iPopSize, fCrossProb, fMutProb, iIterations);
        cout<<"Object created properly."<<endl;
    }
    else{
        vCreate(I_DEFAULT_POP_SIZE, F_DEFAULT_CROSS_PROB, F_DEFAULT_MUT_PROB, I_DEFAULT_ITERATIONS);
        cout<<"Invalid parameters. Object created with default parameters."<<endl;
    }
    i_best_solution_fitness = 0;
    pc_problem = nullptr;
    b_ready = false;
    pv_curr_pop = new vector<CIndividual>;
}

CGeneticAlgorithm::~CGeneticAlgorithm() {
    delete pc_problem;
    delete pv_curr_pop;
}

void CGeneticAlgorithm::vCreate(int iPopSize, float fCrossProb, float fMutProb, int iIterations) {
    i_pop_size = iPopSize;
    f_cross_prob = fCrossProb;
    f_mut_prob = fMutProb;
    i_iterations = iIterations;
}

bool CGeneticAlgorithm::bSetupAlgorithm(CProblem *pcProblem) {
    if(pcProblem != nullptr && pcProblem->bGetIsReady()){
        delete pc_problem;
        pc_problem = pcProblem;
        vClearPrevSolution();
        vGenerateRandomPop();
        b_ready = true;
        cout<<"Genetic Algorithm ready."<<endl;
        return true;
    }else{
        cout<<"Invalid knapsack problem."<<endl;
        return false;
    }
}

void CGeneticAlgorithm::vClearPrevSolution(){
    pv_curr_pop->clear();
    v_pop_fitness.clear();
    v_best_solution.clear();
    i_best_solution_fitness = 0;
}

bool CGeneticAlgorithm::vRun() {
    if(b_ready){
        cout<<"Starting the algorithm."<<endl;
        vRunAlgorithm();
        return true;
    }else {
        cout<<"Genetic Algorithm is not ready to run."<<endl;
        return false;
    }
}

void CGeneticAlgorithm::vRunAlgorithm() {

    for(int i = 0; i < i_iterations; i++){
        vCalcFitness();
        vCalcBestSolution();
        vCross();
        vMutate();
    }
    vCalcFitness();
    vCalcBestSolution();
}

void CGeneticAlgorithm::vCross(){
    pv_new_pop = new vector<CIndividual>;

    while(pv_new_pop->size() < i_pop_size){
        int i_parent_1_id, i_parent_2_id;
        vChooseParents(i_parent_1_id, i_parent_2_id);
        if(!bCrossbreed()){
            pv_new_pop->push_back(pv_curr_pop->at(i_parent_1_id));
            pv_new_pop->push_back(pv_curr_pop->at(i_parent_2_id));
        }else{
            vector<CIndividual> v_children = pv_curr_pop->at(i_parent_1_id).vecCrossbreed(pv_curr_pop->at(i_parent_2_id));
            pv_new_pop->push_back(v_children.at(0));
            pv_new_pop->push_back(v_children.at(1));
        }
    }
    delete pv_curr_pop;
    pv_curr_pop = pv_new_pop;
}

void CGeneticAlgorithm::vMutate() {
    for(int j = 0; j < i_pop_size; j++){
        pv_curr_pop->at(j).vMutate(f_mut_prob);
    }
}

bool CGeneticAlgorithm::bCrossbreed() const {
    uniform_real_distribution<> dist(0.0, 1.0);
    random_device rd;
    mt19937 gen(rd());
    double f_cross = dist(gen);
    return f_cross <= f_cross_prob;
}

bool CGeneticAlgorithm::bValidate(int iPopSize, float fCrossProb, float fMutProb, int iIterations) {
    return (iPopSize > 0 && fCrossProb > 0.0 && fMutProb > 0.0 && iIterations > 0);
}

void CGeneticAlgorithm::vGenerateRandomPop() {
    for(int i = 0; i < i_pop_size;i++){
        CIndividual c_new_individual(pc_problem->iGetItemsNum());
        pv_curr_pop->push_back(std::move(c_new_individual));
    }
}

void CGeneticAlgorithm::vCalcFitness() {
    v_pop_fitness.clear();
    for(int i = 0; i < pv_curr_pop->size(); i++){
        int i_temp = pv_curr_pop->at(i).iCountFitness
                (pc_problem->GetValues(), pc_problem->GetWeights(), pc_problem->iGetCapacity());
        v_pop_fitness.push_back(i_temp);
    }
}

void CGeneticAlgorithm::vCalcBestSolution() {
    int i_best_index = 0;
    bool b_found_better = false;
    for(int i = 0; i < i_pop_size;i++){
        if(i_best_solution_fitness < v_pop_fitness.at(i)){
            b_found_better = true;
            i_best_index = i;
            i_best_solution_fitness = v_pop_fitness.at(i);
        }
    }
    if(b_found_better)
    v_best_solution = pv_curr_pop->at(i_best_index).vecGetGenotype();
}

void CGeneticAlgorithm::vChooseParents(int& i_parent_1_id, int& i_parent_2_id) {
    uniform_int_distribution<int> dist(0, i_pop_size - 1);
    random_device rd;
    mt19937 gen(rd());

    int i_id_candidate_1 = dist(gen);
    int i_id_candidate_2 = dist(gen);
    int i_id_candidate_3 = dist(gen);
    int i_id_candidate_4 = dist(gen);
    if(v_pop_fitness.at(i_id_candidate_1) > v_pop_fitness.at(i_id_candidate_2))
        i_parent_1_id = i_id_candidate_1;
    else
        i_parent_1_id = i_id_candidate_2;
    if(v_pop_fitness.at(i_id_candidate_3) > v_pop_fitness.at(i_id_candidate_4))
        i_parent_2_id = i_id_candidate_3;
    else
        i_parent_2_id = i_id_candidate_4;
}

void CGeneticAlgorithm::vPrintSolution() {
    if(b_ready){
        cout<<"Best solution: "<<endl;
        for(int i = 0; i < v_best_solution.size(); i++){
            cout<<v_best_solution.at(i)<<" ";
        }
        cout<<endl;
        cout<<"Fitness: "<<endl;
        cout<<i_best_solution_fitness<<endl;
    }else
        cout<<"Solution not available - invalid source file."<<endl;

}