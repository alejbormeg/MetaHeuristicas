#include "../include/ES.h"
#include <cstdlib>
#include <random>

void EnfriamientoSimulado(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w, std::mt19937 &generator,int T_final){
    double fitness, fitness_max=0.0;
    std::vector<double> posible_sol;
    int dim=datos[0].first.size();
    double tasa_clas,tasa_red_;

    w=inicializacionBL(dim,generator);
    tasa_clas=LeaveOneOut(datos,w);
	tasa_red_=tasa_red(w);
	fitness_max=funcionEvaluacion(tasa_clas,tasa_red_);

    //int T_actual=CalculaTempInicial();
}

