#include "../include/ES.h"
#include <cstdlib>
#include <random>


double Enfriamiento (double T, double T_inicial, double T_final, double M, std::mt19937 &generator){
    double beta=(T_inicial-T_final)/(M*T_inicial*T_final);
    return T/(1+beta*T);
}

double CalculaTempInicial(double coste, double mu, double phi){
    return (mu * coste)/(-log(phi));
}

void EnfriamientoSimulado(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w, std::mt19937 &generator,double T_final,double mu, double phi){
    
    //Variables que usaremos
    float fitness_s,fitness_s_prima, fitness_max=0.0;
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double dado;
    std::vector<double> s,s_prima;
    int dim=datos[0].first.size();
    double tasa_clas,tasa_red_;
    int contador_vecinos=0,max_vecinos=10*dim;
    int contador_exitos=-1,max_exitos=0.1*max_vecinos; 
    int contador_evaluaciones=0;
    double M=15000/max_vecinos;
    float incremento=0.0;


    //Inicializamos la solucion inicial
    s=inicializacionBL(dim,generator);
    //es la mejor por ahora
    w=s;
    //calculamos su fitness
    tasa_clas=LeaveOneOut(datos,s);
	tasa_red_=tasa_red(s);
	fitness_s=funcionEvaluacion(tasa_clas,tasa_red_);
    //es el mejor por ahora
    fitness_max=fitness_s;
 
    //Calculamos la temperatura inicial
    double T_actual=CalculaTempInicial(fitness_max,mu,phi),T_inicial=T_actual;

    //Bucle principal, las condiciones de parada son: Se alcanza la temperatura mínima, El contador de evaluaciones supera las 15000 o el contador de existos ==0
    while(T_final<T_actual && contador_evaluaciones<15000 && contador_exitos!=0){
        contador_vecinos=0;
        contador_exitos=0;
        while(contador_exitos<max_exitos && contador_vecinos<max_vecinos){
            //Generamos nueva solución mutando una componente
            s_prima=s;
            Mov(s_prima,0.3,generator()%dim,generator);
            //Contamos un nuevo vecino
            contador_vecinos++;
            
            //Calculamos fitness
            tasa_clas=LeaveOneOut(datos,s_prima);
	        tasa_red_=tasa_red(s_prima);
	        fitness_s_prima=funcionEvaluacion(tasa_clas,tasa_red_);
            //Calculamos el incremento
            incremento=fitness_s_prima-fitness_s;
            contador_evaluaciones++;
            //Tiramos el dado para ver si se acepta como éxito en caso de no terner incremento positivo
            dado=dist(generator);

            //Condiciones de éxito
            if(incremento>0 or dado<=exp((-incremento)/(T_actual))){
                //si se dan contamos un éxito
                contador_exitos++;
                //s pasa a ser s_prima
                s=s_prima;
                //actualizamos el fitness
                fitness_s=fitness_s_prima;

                //Si mejora el fitness máximo pues tenemos nueva solución
                if(fitness_s > fitness_max){
                    fitness_max=fitness_s;
                    w=s;
                }
            }
        }
        //enfriamos
        T_actual=Enfriamiento(T_actual,T_inicial,T_final,M,generator);
    }
}

