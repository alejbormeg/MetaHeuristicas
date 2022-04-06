
#include "../include/BL.h"
#include <cstdlib>
#include <random>


std::vector<double> inicializacionBL(int dim){
    std::vector<double> w;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double elem_generado;
    for(int i=0; i<dim; i++){
        elem_generado=dist(generator);
        w.push_back(elem_generado);
    }

    return w;
}

std::vector<double> Mov(std::vector<double> const & w, double sigma, int pos){
    std::default_random_engine generator;
    std::normal_distribution<double> dist(0.0, sigma*sigma);
    std::vector<double> w_mutado=w;
    double z=dist(generator);
    w_mutado[pos]=w_mutado[pos]+z;
    if(w_mutado[pos]>1.0){
        w_mutado[pos]=1.0;
    }

    if(w_mutado[pos]<0.0){
        w_mutado[pos]=0.0;
    }

    return w_mutado;
}

void BusquedaLocal(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w,int semilla){
    srand(semilla); //establecemos semilla
    std::vector<double> w_mutado;
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
    std::cout <<"Empezamos la funcion evaluacione en: " << fmax << std::endl;
    int contador_mut=0; //contador de número de mutaciones
    int contador_ev=0;  //Contador de evaluaciones
    std::cout << "Numero de iteraciones máximas: " << 20*tam_vector << std::endl;

    while(contador_mut<(20*tam_vector) && contador_ev<15000){
        std::random_shuffle(orden_mutaciones.begin(),orden_mutaciones.end());
        mejora=false;
        for(int i=0; i<tam_vector && mejora==false; i++){
            w_mutado=Mov(w,0.3,orden_mutaciones[i]);
            contador_mut++; //aumentamos el número de vecinos
            tasa_clas=LeaveOneOut(datos,w_mutado);

            //std::cout <<"Imprime_precsion obtenida: " << tasa_clas <<std::endl;

            tasa_red_=tasa_red(w_mutado);
            //std::cout <<"Imprime red obtenida: " << tasa_red_ <<std::endl;

            funcion_evaluacion=funcionEvaluacion(tasa_clas,tasa_red_);
            contador_ev++; //aumentamos el número de evaluaciones de la funcion objetivo
            
            if(funcion_evaluacion>fmax){
            //    std::cout <<"\tMejoramos a: " << funcion_evaluacion << std::endl;
                fmax=funcion_evaluacion;
                w=w_mutado;
                mejora=true;
            }
            
        }
        //Salimos
    }

}
