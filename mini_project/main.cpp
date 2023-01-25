#include <iostream>
#include "CIndividual.h"
#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"
#include <chrono>

int main() {

    auto start = std::chrono::high_resolution_clock::now();
    CKnapsackProblem* test_2 = new CKnapsackProblem;
    CKnapsackProblem* test_3 = new CKnapsackProblem(*test_2);
    test_3->vInitialize(R"(C:\Users\pesta\Desktop\studia\sem_3\TEP\mini_project\f1_l-d_kp_10_269.txt)");
    test_2->vInitialize(R"(C:\Users\pesta\Desktop\studia\sem_3\TEP\mini_project\knapsack_test_2.txt)");
    CGeneticAlgorithm ag(10, 0.6, 0.2, 1000);
    ag.bSetupAlgorithm(test_2);
    ag.vRun();
    ag.vPrintSolution();
    ag.bSetupAlgorithm(test_3);
    ag.vRun();
    ag.vPrintSolution();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    cout<<"exec time: "<<duration.count()/1000<<","<<duration.count()%1000 <<" seconds"<<endl;

    return 0;
}
