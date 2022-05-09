#ifndef AGE
#define AGE

#include <vector>
#include <iostream>
#include "utilidades.h"
#include "AGG.h"
#include <ctime> 
#include <random>


/**
 * @brief Calcula el peor fitness del vector
 * 
 * @param vfitness vector de fitness
 * @return int posicion del peor fitness
 */
int CalculaPeor(std::vector<double>&vfitness);

/**
 * @brief Calcula el mejor fitness del vector
 * 
 * @param vfitness vector de fitness
 * @return int posicion del mejor fitness
 */
int CalculaMejor(std::vector<double>&vfitness);

/**
 * @brief Calcula el valor de fitness de todos los elementos de la población
 * 
 * @param poblacion población
 * @param datos datos en los que evaluar
 * @param vfitness vector de fitness
 * @param pos_mejor posicion del mejor vector
 * @param pos_peor posicion del peor vector
 * @param pos_segundo_peor posicion del segundo peor
 */
void CalculaFitness(std::vector<std::vector<double>> & poblacion,std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&vfitness,int &pos_mejor, int &pos_peor, int &pos_segundo_peor);

/**
 * @brief Los mutados compiten para entrar en la población 
 * 
 * @param poblacion Población reemplazada
 * @param mutaciones mutaciones
 * @param datos conjunto de datos que usaremos para entrenar
 * @param vfitness vector de fitness
 * @param pos_mejor posicion del mejor elemento
 * @param pos_peor posicion del peor elemento
 * @param pos_segundo_peor posicion del segundo peor elemento
 */
void ReemplazamientoCompetitivo (std::vector<std::vector<double>> & poblacion,std::vector<std::vector<double>> & mutaciones,std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double> & vfitness, int &pos_mejor, int &pos_peor, int &pos_segundo_peor);

/**
 * @brief Algoritmo que implementa un algoritmo genético estacionario
 * 
 * @param datos conjunto de datos que usaremos para entrenar
 * @param w vector de pesos
 * @param fitness valor de la función objetivo
 * @param tam_pob tamaño de la poblacion
 * @param tipo indica si es con BLX(1) o aritmetico(2)
 * @param gen generador de números aleatorios 
 */
void AlgoritmoGeneticoEstacionario(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w,int tam_pob,int tipo,std::mt19937 & gen);

#endif