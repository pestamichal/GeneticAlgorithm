cmake_minimum_required(VERSION 3.24)
project(mini_project)

set(CMAKE_CXX_STANDARD 11)

add_executable(mini_project main.cpp CKnapsackProblem.h CKnapsackProblem.cpp CGeneticAlgorithm.h CGeneticAlgorithm.cpp CIndividual.cpp CIndividual.h CIndividual.h CProblem.h)
