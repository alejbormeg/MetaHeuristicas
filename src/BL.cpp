
#include "../include/BL.h"
#include <cstdlib>
#include <random>


std::vector<double> inicializacionBL(int dim,std::mt19937 &generator){
    std::vector<double> w;
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double elem_generado;
    for(int i=0; i<dim; i++){
        elem_generado=dist(generator);
        w.push_back(elem_generado);
    }

    return w;
}

void BusquedaLocal(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w,std::mt19937 &generator,int tam_vector, int max_eval){
    std::vector<double> w_mutado=w;
    bool mejora;
    double tasa_clas=0.0;
    double tasa_red_=0.0;
    double funcion_evaluacion=0.0;
    double fmax=0.0;
    std::vector<int> orden_mutaciones;

    for(int i=0;i<tam_vector;i++){
        orden_mutaciones.push_back(i);
    }
    tasa_clas=LeaveOneOut(datos,w);
    tasa_red_=tasa_red(w);
    fmax=funcionEvaluacion(tasa_clas,tasa_red_);
    //std::cout <<"Empezamos la funcion evaluacion en: " << fmax << std::endl;
    int contador_mut=0; //contador de número de mutaciones
    int contador_ev=0;  //Contador de evaluaciones

    while(contador_mut<20*tam_vector && contador_ev<max_eval){
        std::random_shuffle(orden_mutaciones.begin(),orden_mutaciones.end());
        mejora=false;
        for(int i=0; i<tam_vector && mejora==false; i++){
            w_mutado=w;
            Mov(w_mutado,0.3,orden_mutaciones[i],generator);
            contador_mut++; //aumentamos el número de vecinos
            tasa_clas=LeaveOneOut(datos,w_mutado);

            tasa_red_=tasa_red(w_mutado);

            funcion_evaluacion=funcionEvaluacion(tasa_clas,tasa_red_);
            contador_ev++; //aumentamos el número de evaluaciones de la funcion objetivo
            if(funcion_evaluacion>fmax){
                fmax=funcion_evaluacion;
                w=w_mutado;
                mejora=true;
                contador_mut=0;
            }
            
        }
        //Salimos
    }

    //std::cout << "\n ITERACIONES FINALES HASTA CONVERGENCIA :" << contador_ev << std::endl;

}
