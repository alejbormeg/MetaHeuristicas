#ifndef AGG
#define AGG

#include <vector>
#include <iostream>
#include "utilidades.h"
#include <ctime> 


/**
 * @brief Inicializa la población para el algoritmo genético
 * 
 * @param tam_pob tamaño de la poblacion
 * @param dim dimensión de los vectores de la población
 * @return int 
 */
std::vector<std::vector<double>> Inicializar(int tam_pob, int dim);

/**
 * @brief Calcula la solucion y fitness de la poblacion actual
 * 
 * @param poblacion poblacion actual
 * @param solucion solucion encontrada
 * @param fitness funcion evaluacion
 */
void Evaluacion(std::vector<std::vector<double>> & poblacion, std::vector<double> & solucion, double &fitness);

/**
 * @brief Realiza la seleccion de los padres por torneo binario
 * 
 * @param poblacion población inicial
 * @param seleccion padres seleccionados
 */
void Seleccion(std::vector<std::vector<double>> & poblacion,std::vector<std::vector<double>> & seleccion);

/**
 * @brief Realiza el cruce entre los padres
 * 
 * @param seleccion padres seleccionados
 * @param tipo 1 si es BLX y 2 si es CA
 * @param alpha Valor para BLX
 * @param pc Probabilidad de cruce
 * @param cruce Cruces realizados
 */
void Cruce(std::vector<std::vector<double>> & seleccion,int tipo, double alpha,double pc,std::vector<std::vector<double>> & cruce);

/**
 * @brief Mutacion de los cruces
 * 
 * @param cruce cruce actual
 * @param pm probabilidad de mutar
 * @param mutacion población mutada
 */
void Mutacion(std::vector<std::vector<double>> & cruce, double pm,std::vector<std::vector<double>> & mutacion);

/**
 * @brief Reemplaza la población actual por la mutada
 * 
 * @param poblacion Población reemplazada
 * @param poblacion_anterior población anterior
 * @param mutaciones mutaciones
 */
void Reemplazar(std::vector<std::vector<double>> & poblacion,std::vector<std::vector<double>> & poblacion_anterior,std::vector<std::vector<double>> & mutaciones );

/**
 * @brief Algoritmo que implementa la búsqueda local primer mejor
 * 
 * @param datos conjunto de datos que usaremos para entrenar
 * @param w vector de pesos
 * @param fitness valor de la función objetivo
 * @param tam_pob tamaño de la poblacion
 * @param semilla entero para establecer semilla para procesos aleatorios
 */
void AlgoritmoGeneticoGeneracional(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w,int tam_pob,int semilla);


#endif
