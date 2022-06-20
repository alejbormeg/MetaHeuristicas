#ifndef LFBL
#define LFBL

#include <vector>
#include <iostream>
#include "utilidades.h"
#include "LF.h"
#include "AM.h"

/**
 * @brief Algoritmo LeadersAndFollowers hibridado con búsqueda local
 * 
 * @param datos Datos de entrenamiento
 * @param sol solución
 * @param maxevals evaluaciones maximas
 * @param tam_pob tamaño de la población
 * @param dim dimensión del vector
 * @param generator generador de números aleatorios
 */
void LeadersAndFollowersLocalSearch(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double> &sol, int maxevals, int tam_pob, int dim, std::mt19937 &generator);


#endif