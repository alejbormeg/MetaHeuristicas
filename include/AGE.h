#ifndef AGE
#define AGE

#include <vector>
#include <iostream>
#include "utilidades.h"
#include "AGG.h"
#include <ctime> 
#include <random>


/**
 * @brief Los mutados compiten para entrar en la población 
 * 
 * @param poblacion Población reemplazada
 * @param mutaciones mutaciones
 * @param datos conjunto de datos que usaremos para entrenar
 */
void ReemplazamientoCompetitivo (std::vector<std::vector<double>> & poblacion,std::vector<std::vector<double>> & mutaciones,std::vector<std::pair<std::vector<double>,std::string>> &datos);

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