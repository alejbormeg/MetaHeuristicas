#ifndef LFBL
#define LFBL

#include <vector>
#include <iostream>
#include "utilidades.h"
#include "LF.h"
#include "AM.h"

void LeadersAndFollowersLocalSearch(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double> &sol, int maxevals, int tam_pob, int dim, std::mt19937 &generator);


#endif