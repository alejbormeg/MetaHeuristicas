
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

void Mov(std::vector<double> & w, double sigma, int pos){
    std::default_random_engine generator;
    std::normal_distribution<double> dist(0.0, sigma*sigma);
    double z=dist(generator);
    w[pos]=w[pos]+z;
    if(w[pos]>1.0){
        w[pos]=1.0;
    }

    if(w[pos]<0.0){
        w[pos]=0.0;
    }
}