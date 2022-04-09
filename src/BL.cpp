
#include "../include/BL.h"
#include <cstdlib>
#include <random>


std::vector<double> inicializacionBL(int dim,int i){
    std::vector<double> w;
    std::mt19937 gen(i);  // Will be used to obtain a seed for the random number engine
    //std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double elem_generado;
    for(int i=0; i<dim; i++){
        elem_generado=dist(gen);
        w.push_back(elem_generado);
    }

    return w;
}

void Mov(std::vector<double> & w, double sigma, int pos,int i){
    std::mt19937 gen(i);  // Will be used to obtain a seed for the random number engine
    //Se inicializa con la desviación estandar, por eso usamos sigma en lugar de sigma²
    std::normal_distribution<double> dist(0.0,sigma);
    double z=dist(gen);
    w[pos]=w[pos]+z;
    if(w[pos]>1.0){
        w[pos]=1.0;
    }

    if(w[pos]<0.0){
        w[pos]=0.0;
    }

}

void BusquedaLocal(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w,int semilla){
    srand(semilla); //establecemos semilla
    std::vector<double> w_mutado=w;
    bool mejora;
    double tasa_clas=0.0;
    double tasa_red_=0.0;
    double funcion_evaluacion=0.0;
    double fmax=0.0;
    std::vector<int> orden_mutaciones;
    int tam_vector=w.size();

    for(int i=0;i<tam_vector;i++){
        orden_mutaciones.push_back(i);
    }
    tasa_clas=LeaveOneOut(datos,w);
    tasa_red_=tasa_red(w);
    fmax=funcionEvaluacion(tasa_clas,tasa_red_);
    std::cout <<"Empezamos la funcion evaluacion en: " << fmax << std::endl;
    int contador_mut=0; //contador de número de mutaciones
    int contador_ev=0;  //Contador de evaluaciones

    while(contador_mut<(20*tam_vector) && contador_ev<15000){
        std::random_shuffle(orden_mutaciones.begin(),orden_mutaciones.end());
        mejora=false;
        for(int i=0; i<tam_vector && mejora==false; i++){
            w_mutado=w;
            Mov(w_mutado,0.3,orden_mutaciones[i],i);
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

    std::cout << "\n ITERACIONES FINALES HASTA CONVERGENCIA :" << contador_ev << std::endl;

}
