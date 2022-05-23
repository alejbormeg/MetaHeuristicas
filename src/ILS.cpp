#include "../include/ILS.h"
#include <cstdlib>
#include <random>

void MetodoILS(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<std::pair<std::vector<double>,std::string>> &validacion,std::vector<double>&w, std::mt19937 &generator, int tam_vector, int max_eval, int T){
    //Variables necesarias
    double fitness, fitness_max=0.0;
    std::vector<double> solucion_actual;
    int contador=0;
    int iteraciones_por_eval=max_eval/T;
    int dim=datos[0].first.size();
    double tasa_clas,tasa_red_;
    int t=0.1*dim;
    std::vector<int> orden_mutaciones;

    //Rellenamos el vector de posiciones
    for(int i=0;i<tam_vector;i++){
        orden_mutaciones.push_back(i);
    }

    //Inicializamos solución 
    w=inicializacionBL(dim,generator);
    //Aplicamos BL
    BusquedaLocal(datos,w,generator,dim,iteraciones_por_eval);
    tasa_clas=LeaveOneOut(datos,w);
	tasa_red_=tasa_red(w);
	fitness_max=funcionEvaluacion(tasa_clas,tasa_red_);

    while(contador<T){
        //mezclamos el vector de posiciones
        std::random_shuffle(orden_mutaciones.begin(),orden_mutaciones.end());
        //Iniciamos en la mejor solución por el momento
        solucion_actual=w;
        //Mutamos el 10% de sus atributos
        for (int i=0; i<t; i++){
            Mov(solucion_actual,0.4,i,generator);
        }
        //Aplicamos BL
        BusquedaLocal(datos,solucion_actual,generator,dim,iteraciones_por_eval);
        //Obtenemos su tasa de clasificación
        tasa_clas=LeaveOneOut(datos,solucion_actual);
        //Obtenemos su tasa de reducción
		tasa_red_=tasa_red(solucion_actual);
        //Calculamos su fitness
		fitness=funcionEvaluacion(tasa_clas,tasa_red_);
        //Si mejora la solución actual la cambiamos
        if(fitness>fitness_max){
            fitness_max=fitness;
            w=solucion_actual;
        }
        contador++;
    }
}


void MetodoILS_ES(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<std::pair<std::vector<double>,std::string>> &validacion,std::vector<double>&w, std::mt19937 &generator, int tam_vector, int max_eval, int T){
    //Variables necesarias
    double fitness, fitness_max=0.0;
    std::vector<double> solucion_actual;
    int contador=0;
    int iteraciones_por_eval=max_eval/T;
    int dim=datos[0].first.size();
    double tasa_clas,tasa_red_;
    int t=0.1*dim;
    std::vector<int> orden_mutaciones;

    //Rellenamos el vector de posiciones
    for(int i=0;i<tam_vector;i++){
        orden_mutaciones.push_back(i);
    }

    //Inicializamos solución 
    w=inicializacionBL(dim,generator);
    //Aplicamos ES
    EnfriamientoSimulado(datos,w, generator,0.001,0.3, 0.3);
    tasa_clas=LeaveOneOut(datos,w);
	tasa_red_=tasa_red(w);
	fitness_max=funcionEvaluacion(tasa_clas,tasa_red_);

    while(contador<T){
        //mezclamos el vector de posiciones
        std::random_shuffle(orden_mutaciones.begin(),orden_mutaciones.end());
        //Iniciamos en la mejor solución por el momento
        solucion_actual=w;
        //Mutamos el 10% de sus atributos
        for (int i=0; i<t; i++){
            Mov(solucion_actual,0.4,i,generator);
        }
        //Aplicamos ES
        EnfriamientoSimulado(datos,solucion_actual, generator,0.001,0.3, 0.3);
        //Obtenemos su tasa de clasificación
        tasa_clas=LeaveOneOut(datos,solucion_actual);
        //Obtenemos su tasa de reducción
		tasa_red_=tasa_red(solucion_actual);
        //Calculamos su fitness
		fitness=funcionEvaluacion(tasa_clas,tasa_red_);
        //Si mejora la solución actual la cambiamos
        if(fitness>fitness_max){
            fitness_max=fitness;
            w=solucion_actual;
        }
        contador++;
    }

}

