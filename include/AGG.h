#ifndef AGG
#define AGG

#include <vector>
#include <iostream>
#include "utilidades.h"
#include <ctime> 
#include <random>


/**
 * @brief Inicializa la población para el algoritmo genético
 * 
 * @param tam_pob tamaño de la poblacion
 * @param dim dimensión de los vectores de la población
 * @param generator generador de números aleatorios
 * @return población de cromosomas inicial
 */
std::vector<std::vector<double>> Inicializar(int tam_pob, int dim,std::mt19937 &generator);

/**
 * @brief Calcula la solucion y fitness de la poblacion actual
 * 
 * @param poblacion poblacion actual
 * @param solucion solucion encontrada
 * @param fitness funcion evaluacion
 */
void Evaluacion(std::vector<std::vector<double>> & poblacion,std::vector<std::pair<std::vector<double>,std::string>> &datos, std::vector<double> & solucion, double &fitness);

/**
 * @brief Realiza la seleccion de los padres por torneo binario
 * 
 * @param poblacion población inicial
 * @param seleccion padres seleccionados
 * @param generator generador de números aleatorios
 */
void Seleccion(std::vector<std::vector<double>> & poblacion,std::vector<std::vector<double>> & seleccion,std::mt19937 &generator);

/**
 * @brief Aplica el algoritmo de cruce BLX
 * 
 * @param c1 padre 1
 * @param c2 padre 2
 * @param cruce Poblacion de cruces dónde añadiremos los hijos
 * @param alpha parámetro alpha del algoritmo
 * @param generator generador de números aleatorios
 */
void BLX(std::vector<double> const &c1,std::vector<double> const &c2,std::vector<std::vector<double>> & cruce, double alpha,std::mt19937 &generator);

/**
 * @brief Realiza el cruce entre los padres
 * 
 * @param seleccion padres seleccionados
 * @param tipo 1 si es BLX y 2 si es CA
 * @param alpha Valor para BLX
 * @param pc Probabilidad de cruce
 * @param cruce Cruces realizados
 * @param generator generador de números aleatorios
 */
void Cruce(std::vector<std::vector<double>> const & seleccion,int tipo, double alpha,double pc,std::vector<std::vector<double>> & cruce,std::mt19937 &generator);

/**
 * @brief Operador de mutación
 * @param w vector que elegimos mutar 
 * @param sigma desv típica de la distribución normal
 * @param pos gen a mutar
 * @param generator generador de números aleatorios
 */
void Mov(std::vector<double> & w, double sigma, int pos,std::mt19937 &generator);

/**
 * @brief Mutacion de los cruces
 * 
 * @param cruce cruce actual
 * @param pm probabilidad de mutar
 * @param generator generador de números aleatorios 
 */
void Mutacion(std::vector<std::vector<double>> & cruce, double pm,std::mt19937 &generator);

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
