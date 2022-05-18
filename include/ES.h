#ifndef ES
#define ES

#include <vector>
#include <iostream>
#include "utilidades.h"
#include "BL.h" 


/**
 * @brief Algoritmo Enfriamiento simulado
 * 
 * @param datos datos para el entrenamiento
 * @param w solución
 * @param generator generador de números aleatorios
 * @param T_final Temperatura final
 */
void EnfriamientoSimulado(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w, std::mt19937 &generator,int T_final);

#endif