#include "../include/ILS.h"
#include <cstdlib>
#include <random>

void MetodoILS(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<std::pair<std::vector<double>,std::string>> &validacion,std::vector<double>&w, std::mt19937 &generator, int tam_vector, int max_eval, int T){
    double fitness, fitness_max=0.0;
    std::vector<double> solucion_actual;
    int contador=0;
    int iteraciones_por_eval=max_eval/T;
    int dim=datos[0].first.size();
    double tasa_clas,tasa_red_;
    int t=0.1*dim;
    std::vector<int> orden_mutaciones;

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
        std::random_shuffle(orden_mutaciones.begin(),orden_mutaciones.end());
        solucion_actual=w;
        //Mutamos el 10%
        for (int i=0; i<t; i++){
            Mov(solucion_actual,0.4,i,generator);
        }
        BusquedaLocal(datos,solucion_actual,generator,dim,iteraciones_por_eval);
		//tasa_clas=Evaluacion(datos,validacion,solucion_actual);
        tasa_clas=LeaveOneOut(datos,solucion_actual);
		tasa_red_=tasa_red(solucion_actual);
		fitness=funcionEvaluacion(tasa_clas,tasa_red_);
        if(fitness>fitness_max){
            fitness_max=fitness;
            w=solucion_actual;
        }
        contador++;
    }
}
