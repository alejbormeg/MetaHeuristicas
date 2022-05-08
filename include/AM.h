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
 * @brief Calcula los índices de los mejores
 * 
 * @param vfitness vector de fitness
 * @param n número de mejores que buscamos
 * @return std::vector<int> índices de los mejores
 */
std::vector<int> CalculaMejores(std::vector<double> vfitness, int n);

/**
 * @brief Método de reemplazo y evaluacion para el caso de meméticos, la diferencia es que en este caso tenemos un vector con los resultados de fitness
 * para poder obtener rápidamente los 0.1*N mejores en caso de ser necesario 
 * 
 * @param poblacion población
 * @param mutaciones matriz de mutaciones
 * @param datos datos para evaluar
 * @param w vector sol
 * @param fitness fitness de la sol
 * @param vfitness vector con los valores de fitness para la población
 */
void ReemplazarYEvaluarAM(std::vector<std::vector<double>> & poblacion,std::vector<std::vector<double>> const & mutaciones,std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double> & w,double &fitness,std::vector<double> & vfitness);
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
 * @param mejores indica si se hace la versión con los mejores cromosomas (true) o no (false)
 * @param gen generador de num aleatorios
 */
void AlgoritmoMemetico(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w,int tam_pob,int semilla,int tipo,double pls, bool mejores, std::mt19937 & gen);


#endif