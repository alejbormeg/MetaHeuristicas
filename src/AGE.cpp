#include "../include/AGE.h"
#include <cstdlib>


int CalculaPeor(std::vector<double>&vfitness){
    double min=100.0;
    int peor=0;

    for(int i=0; i<vfitness.size();i++){
        if(vfitness[i]<min){
            min=vfitness[i];
            peor=i;
        }
    }
    return peor;
}

int CalculaMejor(std::vector<double>&vfitness){
    double max=0.0;
    int mejor=0;

    for(int i=0; i<vfitness.size();i++){
        if(vfitness[i]>max){
            max=vfitness[i];
            mejor=i;
        }
    }
    return mejor;
}

void CalculaFitness(std::vector<std::vector<double>> & poblacion,std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&vfitness,int &pos_mejor, int &pos_peor){
    //Evaluamos todos los vectores de la población
    double tasa_clas=0.0, tasa_red_=0.0,fitness=0.0;
    double mejorfitness=0.0;
    double peorfitness=100.0;
    std::vector<double> v;
    for(int i=0; i<poblacion.size();i++){
        v=poblacion[i];
        //Calculamos el valor de fitness de v1
        tasa_clas=LeaveOneOut(datos,v);
        tasa_red_=tasa_red(v);
        fitness=funcionEvaluacion(tasa_clas,tasa_red_);
        vfitness.push_back(fitness);
        if(fitness>mejorfitness){
            mejorfitness=fitness;
            pos_mejor=i;
        }

        if(fitness<peorfitness){
            peorfitness=fitness;
            pos_peor=i;
        }
    }
}

void ReemplazamientoCompetitivo (std::vector<std::vector<double>> & poblacion,std::vector<std::vector<double>> & mutaciones,std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double> & vfitness, int pos_mejor, int pos_peor){
    double fitness1=0.0,fitness2=0.0, minimofitness=100.0;
    double tasa_clas=0.0, tasa_red_=0.0;
    int indice_peor=0;
    std::vector<double> v;

    for (int k=0; k<2; k++){
        //Obtenemos el fitness del primero de los mutados
        v=mutaciones[k];
        tasa_clas=LeaveOneOut(datos,v);
        tasa_red_=tasa_red(v);
        fitness1=funcionEvaluacion(tasa_clas,tasa_red_);
        
        if(vfitness[pos_peor]<fitness1){
            vfitness[pos_peor]=fitness1;
            pos_peor=CalculaPeor(vfitness);
            pos_mejor=CalculaMejor(vfitness);
        }
    }
}

void AlgoritmoGeneticoEstacionario(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w,int tam_pob,int semilla,int tipo){
    srand(semilla); //establecemos semilla
    std::mt19937 gen(semilla); //generador
    std::vector<std::vector<double>> poblacion,seleccion,cruce;
    std::vector<double>solucion;
    std::vector<double> vector_fitness;
    int evaluaciones=0;
    int dim=datos[0].first.size();
    int pos_mejor=0;
    int pos_peor=0;

    poblacion=Inicializar(tam_pob,dim,gen);
    CalculaFitness(poblacion,datos,vector_fitness,pos_mejor,pos_peor);

    while(evaluaciones<15000){
        std::cout << "Iteraciones: " << evaluaciones << std::endl;
        Seleccion(datos,poblacion,seleccion,gen,2);
        Cruce(seleccion,tipo,0.3,1,cruce,gen);
        Mutacion(cruce,0.1,gen);
        ReemplazamientoCompetitivo(poblacion,cruce,datos,vector_fitness,pos_mejor,pos_peor);
        solucion=poblacion[pos_mejor];

        evaluaciones+=2;
        seleccion.clear();
        cruce.clear();
    }
    w=solucion;
}
