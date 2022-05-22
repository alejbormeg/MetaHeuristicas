#ifndef BMB
#define BMB

#include <vector>
#include <iostream>
#include "utilidades.h"
#include "BL.h" 



/**
 * @brief Ejecuta el método de Busqueda Multiarranque Básica
 * 
 * @param datos datos de entrenamiento
 * @param w vector solucion
 * @param generator generador de números aleatorios
 * @param tam_vector tamaño de vector
 * @param max_eval maximo de evaluaciones
 * @param T numero de iteraciones
 */
void BusquedaMultiarranqueBasica(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w, std::mt19937 &generator, int tam_vector, int max_eval, int T);

#endif