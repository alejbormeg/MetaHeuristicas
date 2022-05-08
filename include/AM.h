#ifndef AM
#define AM

#include <vector>
#include <iostream>
#include "utilidades.h"
#include "AGG.h"
#include "BL.h"
#include <ctime> 
#include <random>



/**
 * @brief Búsqueda Local adaptada para Algoritmos Meméticos
 * 
 * @param datos Datos para entrenar 
 * @param w cromosoma al que aplicamos BL
 * @param contador_evaluaciones Contador de evaluaciones
 * @param generator generador de números aleatorios
 */
void BusquedaLocalAM(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w,int &contador_evaluaciones,std::mt19937 &generator);

/**
 * @brief Algoritmo que implementa el algoritmo memético (10,1.0) (10,0.1) (10, 0.1*N) según los parámetros
 * 
 * @param datos conjunto de datos que usaremos para entrenar
 * @param w vector de pesos
 * @param fitness valor de la función objetivo
 * @param tam_pob tamaño de la poblacion
 * @param semilla entero para establecer semilla para procesos aleatorios
 * @param tipo indica si es con BLX(1) o aritmetico(2)
 * @param pls probabilidad de selección de cromosoma para BL
 */
void AlgoritmoMemetico(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w,int tam_pob,int semilla,int tipo, double pls);


#endif