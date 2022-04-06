
#ifndef BL
#define BL

#include <vector>
#include <iostream>
#include "utilidades.h"
#include <ctime> 



/**
 * @brief Inicializa el vector de pesos usando una distribución uniforme [0,1]
 * 
 * @param dim dimensión del vector de pesos
 * @return std::vector<double> vector de pesos
 */
std::vector<double> inicializacionBL(int dim,int i);

/**
 * @brief Función que implementa el desarrollo de un nuevo vecino a la solución actual mutando con una distribución normal [0,sigma^2] una componente.
 * 
 * @param w Vector de pesos
 * @param sigma Desviación típica de la normal que usaremos
 * @param pos Índice del atributo a mutar
 */
void Mov(std::vector<double> &w,double sigma,int pos,int i);

/**
 * @brief Algoritmo que implementa la búsqueda local primer mejor
 * 
 * @param datos conjunto de datos que usaremos para entrenar
 * @param w vector de pesos
 * @param semilla entero para establecer semilla para procesos aleatorios
 */
void BusquedaLocal(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w,int semilla);

#endif
