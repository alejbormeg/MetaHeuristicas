#include "../include/AGE.h"
#include <cstdlib>


void ReemplazamientoCompetitivo (std::vector<std::vector<double>> & poblacion,std::vector<std::vector<double>> & mutaciones,std::vector<std::pair<std::vector<double>,std::string>> &datos){
    double fitness1=0.0, minimofitness=100.0;
    double tasa_clas=0.0, tasa_red_=0.0;
    int indice_peor=0;
    std::vector<double> v;

    for(int k=0; k<2; k++){
        //Evaluamos todos los vectores de la nueva población
        for(int i=0; i<poblacion.size();i++){
            v=poblacion[i];
            //Calculamos el valor de fitness de v1
            tasa_clas=LeaveOneOut(datos,v);
            tasa_red_=tasa_red(v);
            fitness1=funcionEvaluacion(tasa_clas,tasa_red_);
            if(fitness1<minimofitness){
                indice_peor=i;
                minimofitness=fitness1;
            }
        }

        //Obtenemos el fitness del primero de los mutados
        v=mutaciones[k];
        tasa_clas=LeaveOneOut(datos,v);
        tasa_red_=tasa_red(v);
        fitness1=funcionEvaluacion(tasa_clas,tasa_red_);

        //Si es mejor que el fitness del peor
        if(fitness1>minimofitness){
            //TODO REVISAR ESTO
            poblacion[indice_peor]=v;
        }
    }
}

void AlgoritmoGeneticoEstacionario(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w,int tam_pob,int semilla,int tipo){
    srand(semilla); //establecemos semilla
    std::mt19937 gen(semilla); //generador
    std::vector<std::vector<double>> poblacion,seleccion,cruce;
    std::vector<double>solucion;
    int evaluaciones=0;
    double fitness = 0.0;
    int dim=datos[0].first.size();
    int t=0;

    poblacion=Inicializar(tam_pob,dim,gen);
    Evaluacion(poblacion,datos,solucion,fitness);
    
    while(evaluaciones<15000){
        std::cout << "Iteraciones: " << evaluaciones << std::endl;
        Seleccion(datos,poblacion,seleccion,gen,2);
        Cruce(seleccion,tipo,0.3,1,cruce,gen);
        Mutacion(cruce,0.1,gen);
        ReemplazamientoCompetitivo(poblacion,cruce,datos);
        Evaluacion(poblacion,datos,solucion,fitness);
        evaluaciones+=2;
        seleccion.clear();
        cruce.clear();
    }
    w=solucion;
}
