#include "../include/BMB.h"
#include <cstdlib>
#include <random>


/**
 * @brief Ejecuta el método de Busqueda Multiarranque Básica
 * 
 * @param datos datos de entrenamiento
 * @param validacion datos de validacion
 * @param w vector solucion
 * @param generator generador de números aleatorios
 * @param tam_vector tamaño de vector
 * @param max_eval maximo de evaluaciones
 * @param T numero de iteraciones
 */
void BusquedaMultiarranqueBasica(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<std::pair<std::vector<double>,std::string>> &validacion,std::vector<double>&w, std::mt19937 &generator, int tam_vector, int max_eval, int T){
    double fitness, fitness_max=0.0;
    std::vector<double> solucion_actual;

    int iteraciones_por_eval=max_eval/T;
    int dim=datos[0].first.size();
    double tasa_clas,tasa_red_;

    for(int i=0; i<T; i++){
        solucion_actual=inicializacionBL(dim,generator);
        BusquedaLocal(datos,solucion_actual,generator,dim,iteraciones_por_eval);
		//tasa_clas=Evaluacion(datos,validacion,solucion_actual);
        tasa_clas=LeaveOneOut(datos,solucion_actual);
		tasa_red_=tasa_red(solucion_actual);
		fitness=funcionEvaluacion(tasa_clas,tasa_red_);
        if(fitness>fitness_max){
            fitness_max=fitness;
            w=solucion_actual;
        }
    }
}
