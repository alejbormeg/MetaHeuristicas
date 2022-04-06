
#ifndef RELIEF
#define RELIEF
#include <cstdlib>      // std::rand, std::srand
#include <utilidades.h>
using namespace std;

/**
 * @brief Calcula la distancia al enemigo más cercano de un elemento.
 * 
 * @param entrenamiento vector de datos
 * @param elemento índice del elemento 
 * @return vector<double> distancia componente a componente entre el elemento y su enemigo más cercano
 */
vector<double> distanciaEnemigoMascercano(vector<pair<vector<double>,std::string>> &entrenamiento, int elemento);

/**
 * @brief Calcula la distancia al amigo más cercano de un elemento.
 * 
 * @param entrenamiento vector de datos
 * @param elemento índice del elemento 
 * @return vector<double> distancia componente a componente entre el elemento y su amigo más cercano
 */
vector<double> distanciaAmigoMasCercano(vector<pair<vector<double>,std::string>> &entrenamiento, int elemento);

/**
 * @brief Función que implementa el método RELIEF para la obtención de un vector de pesos
 * 
 * @param entrenamiento vector de datos de entrenamiento
 * @return vector<double> vector de pesos obtenido
 */
vector<double> metodoRELIEF(vector<pair<vector<double>,std::string>> &entrenamiento);

#endif