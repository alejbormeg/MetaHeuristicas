#ifndef LF
#define LF

#include <vector>
#include <iostream>
#include "utilidades.h"
#include "AGG.h"

/**
 * @brief Create a trial 
 * 
 * @param leader vector from Leaders Set
 * @param follower vector from Followers Set
 * @param generator random number generator
 * @return vector<double> trial
 */
std::vector<double> create_trial(std::vector<double> &leader, std::vector<double> &follower, std::mt19937 &generator);


/**
 * @brief Computes the median of a vector
 * 
 * @param scores vector
 * @return double median
 */
double CalcMHWScore(std::vector<double> scores);

std::vector<std::vector<double>> merge_populations(std::vector<std::vector<double>> &L, std::vector<std::vector<double>> &F,std::vector<double> &l_fitness,std::vector<double> &f_fitness, std::mt19937 &generator);

void LeadersAndFollowers(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double> &sol, int maxevals, int tam_pob, int dim, std::mt19937 &generator);


#endif