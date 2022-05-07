#ifndef AGE
#define AGE

#include <vector>
#include <iostream>
#include "utilidades.h"
#include "AGG.h"
#include <ctime> 
#include <random>


/**
 * @brief Calcula el valor de fitness de todos los elementos de la población
 * 
 * @param poblacion población
 * @param datos datos en los que evaluar
 * @param vfitness vector de fitness
 */
void CalculaFitness(std::vector<std::vector<double>> & poblacion,std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&vfitness);

/**
 * @brief Los mutados compiten para entrar en la población 
 * 
 * @param poblacion Población reemplazada
 * @param mutaciones mutaciones
 * @param datos conjunto de datos que usaremos para entrenar
 * @param vfitness vector de fitness
 */
void ReemplazamientoCompetitivo (std::vector<std::vector<double>> & poblacion,std::vector<std::vector<double>> & mutaciones,std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double> & vfitness);

/**
 * @brief Algoritmo que implementa un algoritmo genético estacionario
 * 
 * @param datos conjunto de datos que usaremos para entrenar
 * @param w vector de pesos
 * @param fitness valor de la función objetivo
 * @param tam_pob tamaño de la poblacion
 * @param semilla entero para establecer semilla para procesos aleatorios
 * @param tipo indica si es con BLX(1) o aritmetico(2)
 */
void AlgoritmoGeneticoEstacionario(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w,int tam_pob,int semilla,int tipo);

#endif