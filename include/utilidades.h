
#ifndef UTILIDADES
#define UTILIDADES

#include <algorithm>    // std::random_shuffle
#include <string>
#include <cassert>
#include<cmath>
#include <vector>


/**
 * @brief Función que calcula la distancia euclídea entre dos vectores
 * 
 * @param e1 Primer vector
 * @param e2 Segundo vector
 * @return double distancia euclídea entre e1 y e2
 */
double distanciaEuclidea(std::vector<double> &e1, std::vector<double> &e2);

/**
 * @brief Función que calcula la distancie euclídea ponderada con un vector de pesos.
 * 
 * @param e1 Primer vector
 * @param e2 Segundo vector
 * @param w Vector de pesos
 * @return double distancia ponderada entre e1 y e2
 */
double distanciaPonderada(std::vector<double> &e1, std::vector<double> &e2, std::vector<double> &w);

/**
 * @brief Calcula la tasa de reducción dado un vector de pesos w. Para ello se calcula el porcentaje de valores de w por debajo de 0.1
 * 
 * @param w Vector de pesos
 * @return double Tasa de reducción.
 */
double tasa_red (std::vector<double>&w);

/**
 * @brief Función de evaluación
 * 
 * @param tasa_clas Precisión
 * @param tasa_red Tasa de reducción 
 * @return double Función de evaluación
 */
double funcionEvaluacion(double tasa_clas, double tasa_red);

/**
 * @brief Función que normaliza los datos para establecerlos en el intervalo [0,1]
 * 
 * @param datos Vector de datos a normalizar
 */
void Normalizar( std::vector<std::pair<std::vector<double>, std::string>> &datos);
/**
 * @brief Sobrecarga del operador + entre vectores para realizar suma componente a componente
 * 
 * @tparam T tipo de dato que contiene el vector
 * @param a vector 
 * @param b vector 
 * @return std::vector<T> suma componente a componente de a y b
 */
template <typename T>
std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b)
{
    assert(a.size() == b.size());

    std::vector<T> result;

    for(int i=0; i<a.size(); i++){
		result.push_back(a[i]+b[i]);
	}

    return result;
}

/**
 * @brief Sobrecarga del operador - entre vectores para realizar resta componente a componente
 * 
 * @tparam T tipo de dato que contiene el vector
 * @param a vector 
 * @param b vector 
 * @return std::vector<T> resta componente a componente de a y b
 */
template <typename T>
std::vector<T> operator-(const std::vector<T>& a, const std::vector<T>& b)
{
    assert(a.size() == b.size());

    std::vector<T> result;

    for(int i=0; i<a.size(); i++){
		result.push_back(a[i]-b[i]);
	}

    return result;
}

/**
 * @brief Función que implementa el clasificador 1-NN usado en la práctica.
 * 
 * @param datos vector de datos 
 * @param nuevo_ejemplo ejemplo a clasificar
 * @param w vector de pesos
 * @param posicion índice que ocupa el elemento en los datos
 * @return string clase del elemento predicha 
 */
std::string Clasificador1NN( std::vector<std::pair<std::vector<double>,std::string>> &datos, std::vector<double> &nuevo_ejemplo,std::vector<double> &w, int posicion=-1);

/**
 * @brief Función para realizar estrategia LeaveOneOut y calcular si el vector de entrenamiento clasifica bien sus propios ejemplos sin tenerlos en cuenta.
 * 
 * @param entrenamiento datos que usaremos
 * @param w vector de pesos
 * @return double precisión obtenida
 */
double LeaveOneOut (std::vector<std::pair<std::vector<double>,std::string>> &entrenamiento, std::vector<double> &w);

/**
 * @brief Función para calcular la precisión usando los datos de entrenamiento para clasificar los de validación.
 * 
 * @tparam T etiqueta
 * @param entrenamiento vector de datos de entrenamiento
 * @param validacion  vector de datos de validación
 * @param w vector de pesos
 * @return double 
 */
template <typename T>
double Evaluacion (std::vector<std::pair<std::vector<double>,T>> &entrenamiento,std::vector<std::pair<std::vector<double>,T>> &validacion, std::vector<double> &w){
	int num_correctos=0;
	int num_elementos=validacion.size();
	T etiqueta_predicha;

	for(int i=0; i<validacion.size();i++){
		etiqueta_predicha=Clasificador1NN(entrenamiento,validacion[i].first,w);
		if(etiqueta_predicha==validacion[i].second){
			num_correctos++;
		}
	}	

	return 100*((double)(num_correctos)/num_elementos);
}

/**
 * @brief Función para dividir un conjunto de datos en particiones para 5-fold Cross Validation
 * 
 * @param datos Conjunto de datos que queremos dividir
 * @param entrenamiento vector de datos de entrenamiento
 * @param validacion vector de datos de validación
 * @param k indica la partición correspondiente a valiación
 */
//El std::vector datos ya debe venir mezclado, prepara para entrenar con 80% y dejar 20% validacion
void Prepara5FoldCrossVal(std::vector<std::pair<std::vector<double>,std::string>> & datos,std::vector<std::pair<std::vector<double>,std::string>> & entrenamiento,std::vector<std::pair<std::vector<double>,std::string>> & validacion,int k);

#endif