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
void Evaluacion(std::vector<std::vector<double>> const & poblacion,std::vector<std::pair<std::vector<double>,std::string>> &datos, std::vector<double> & solucion, double &fitness);

/**
 * @brief Realiza la seleccion de los padres por torneo binario
 * 
 * @param datos conjunto de datos que usaremos para entrenar
 * @param poblacion población inicial
 * @param seleccion padres seleccionados
 * @param generator generador de números aleatorios
 * @param tam tamaño de la selección (para poder usarse en el AGE)
 */
void Seleccion(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<std::vector<double>> const & poblacion,std::vector<std::vector<double>> & seleccion,std::mt19937 &generator,int tam);

/**
 * @brief Implementa el cruce aritmético
 * 
 * @param c1 padre 1
 * @param c2 padre 2
 * @param cruce matriz con los cruces
 * @param generator generador de números aleatorios
 */
void ARITMETICO(std::vector<double> const &c1,std::vector<double> const &c2,std::vector<std::vector<double>> & cruce,std::mt19937 &generator);

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
 * @brief Comprueba si el vector w está en la población 
 * 
 * @param poblacion población
 * @param w vector que queremos comprobar
 * @return true si está
 * @return false si no está
 */
bool Contiene(std::vector<std::vector<double>> const & poblacion,std::vector<double> & w);

/**
 * @brief Reemplaza la población actual por la mutada
 * 
 * @param poblacion Población reemplazada
 * @param mutaciones mutaciones
 * @param datos conjunto de datos que usaremos para entrenar
 * @param w mejor solución de la población anterior
 * @param fitness fitness de la mejor solución de la población anterior
 */
void ReemplazarYEvaluar(std::vector<std::vector<double>> & poblacion,std::vector<std::vector<double>> const & mutaciones,std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double> & w,double &fitness);

/**
 * @brief Algoritmo que implementa un algoritmo genético generacional elitista
 * 
 * @param datos conjunto de datos que usaremos para entrenar
 * @param w vector de pesos
 * @param fitness valor de la función objetivo
 * @param tam_pob tamaño de la poblacion
 * @param semilla entero para establecer semilla para procesos aleatorios
 * @param tipo indica si es con BLX(1) o aritmetico(2)
 */
void AlgoritmoGeneticoGeneracional(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w,int tam_pob,int semilla,int tipo);



#endif
