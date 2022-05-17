
#ifndef BL
#define BL

#include <vector>
#include <iostream>
#include "utilidades.h"
#include <ctime> 



/**
 * @brief Inicializa el vector de pesos usando una distribución uniforme [0,1]
 * 
 * @param dim dimensión del vector de pesos
 * @return std::vector<double> vector de pesos
 */
std::vector<double> inicializacionBL(int dim,int i);

/**
 * @brief Algoritmo que implementa la búsqueda local primer mejor
 * 
 * @param datos conjunto de datos que usaremos para entrenar
 * @param w vector de pesos
 * @param generator generador de números aleatorios
 * @param tam_vector tamaño del vector solucion
 * @param max_eval numero max de evaluaciones
 */
void BusquedaLocal(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w, std::mt19937 &generator, int tam_vector, int max_eval);

#endif
