#ifndef ILS
#define ILS

#include <vector>
#include <iostream>
#include "utilidades.h"
#include "BL.h" 



/**
 * @brief Algoritmo que implementa el algoritmo ILS
 * 
 * @param datos conjunto de datos que usaremos para entrenar
 * @param w vector de pesos
 * @param generator generador de números aleatorios
 * @param tam_vector tamaño del vector solucion
 * @param max_eval numero de evaluaciones
 * @param T repeticiones de la BL
 */
void MetodoILS(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<std::pair<std::vector<double>,std::string>> &validacion,std::vector<double>&w, std::mt19937 &generator, int tam_vector, int max_eval, int T);

#endif