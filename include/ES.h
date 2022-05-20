#ifndef ES
#define ES

#include <vector>
#include <iostream>
#include "utilidades.h"
#include "BL.h" 



/**
 * @brief Función que calcula el enfriamiento
 * 
 * @param T temperatura actual
 * @param T_inicial temperatura inicial
 * @param T_final temperatura final
 * @param M valor de M
 * @param generator generador de números aleatorios
 * @return double temperatura tras enfriamiento
 */
double Enfriamiento (double T, double T_inicial, double T_final, int M, std::mt19937 &generator);

/**
 * @brief Calcula la temperatura inicial
 * 
 * @param coste valor de fitness del vector solución inicial
 * @param mu valor de mu
 * @param phi valor de phi
 * @return double 
 */
double CalculaTempInicial(double coste, double mu, double phi);

/**
 * @brief Algoritmo Enfriamiento simulado
 * 
 * @param datos datos para el entrenamiento
 * @param w solución
 * @param generator generador de números aleatorios
 * @param T_final Temperatura final
 * @param mu valor de mu para Temperatura inicial
 * @param phi valor de phi para la temperatura inicial
 */
void EnfriamientoSimulado(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w, std::mt19937 &generator,double T_final,double mu, double phi);

#endif