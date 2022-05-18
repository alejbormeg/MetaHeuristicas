#include "../include/ES.h"
#include <cstdlib>
#include <random>


double Enfriamiento (double T, double T_inicial, double T_final, int M){
    double beta=(T_inicial-T_final)/(M*T_inicial*T_final);
    //return T/(1+beta*T);
    return 0.9*T;
}

double CalculaTempInicial(double coste, double mu, double phi){
    return (mu * coste)/(-log(phi));
}

void EnfriamientoSimulado(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w, std::mt19937 &generator,int T_final,double mu, double phi){
    double fitness_s,fitness_s_prima, fitness_max=0.0;
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double dado;
    std::vector<double> s,s_prima;
    int dim=datos[0].first.size();
    double tasa_clas,tasa_red_;
    int contador_vecinos=0,max_vecinos=10*dim;
    int contador_exitos=-1,max_exitos=0.1*max_vecinos; 
    int contador_evaluaciones=0;
    int M=15000/max_vecinos;
    double incremento=0.0;

    s=inicializacionBL(dim,generator);
    w=s;
    tasa_clas=LeaveOneOut(datos,s);
	tasa_red_=tasa_red(s);
	fitness_s=funcionEvaluacion(tasa_clas,tasa_red_);
    fitness_max=fitness_s;
    double T_actual=CalculaTempInicial(fitness_max,mu,phi),T_inicial=T_actual;

    while(T_final<T_actual && contador_evaluaciones<15000 && contador_exitos!=0){
        contador_vecinos=0;
        contador_exitos=0;
        while(contador_exitos<max_exitos && contador_vecinos<max_vecinos){
            //std::cout << "\ncontador de exitos: " << contador_exitos << std::endl;
            //std::cout << "\ncontador evaluaciones: " << contador_evaluaciones << std::endl;

            s_prima=s;
            
            Mov(s_prima,0.3,generator()%dim,generator);
            contador_vecinos++;

            tasa_clas=LeaveOneOut(datos,s_prima);
	        tasa_red_=tasa_red(s_prima);
	        fitness_s_prima=funcionEvaluacion(tasa_clas,tasa_red_);
            incremento=fitness_s_prima-fitness_s;
            contador_evaluaciones++;
            dado=dist(generator);

            if(incremento>0 || dado<=exp(-incremento/(5*T_actual))){
                contador_exitos++;
                s=s_prima;
                fitness_s=fitness_s_prima;
                if(fitness_s > fitness_max){
                    fitness_max=fitness_s;
                    w=s;
                }
            }
        }
        T_actual=Enfriamiento(T_actual,T_inicial,T_final,M);
    }
}

