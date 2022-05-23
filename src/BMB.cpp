#include "../include/BMB.h"
#include <cstdlib>
#include <random>


void BusquedaMultiarranqueBasica(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w, std::mt19937 &generator, int tam_vector, int max_eval, int T){
    //Variables necesarias
    double fitness, fitness_max=0.0;
    std::vector<double> solucion_actual;
    int iteraciones_por_eval=max_eval/T;
    int dim=datos[0].first.size();
    double tasa_clas,tasa_red_;

    //Realizamos T veces el siguiente proceso
    for(int i=0; i<T; i++){
        //Geramos sol inicial aleatoria
        solucion_actual=inicializacionBL(dim,generator);
        //Le aplicamos BL
        BusquedaLocal(datos,solucion_actual,generator,dim,iteraciones_por_eval);
        //Obtenemos tasa de clasificación
        tasa_clas=LeaveOneOut(datos,solucion_actual);
        //Obtenemos tasa de reducción
		tasa_red_=tasa_red(solucion_actual);
        //Obtenemos fitness
		fitness=funcionEvaluacion(tasa_clas,tasa_red_);
        //Si mejoramos la mejor solución actual la cambiamos
        if(fitness>fitness_max){
            fitness_max=fitness;
            w=solucion_actual;
        }
    }
}
