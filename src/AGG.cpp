#include "../include/AGG.h"
#include <cstdlib>
#include <random>

std::vector<std::vector<double>> Inicializar(int tam_pob, int dim){
    std::vector<double> v;
    std::mt19937 gen(0); //generador
    std::vector<std::vector<double>> poblacion;
      // Will be used to obtain a seed for the random number engine
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double elem_generado;

    for(int k=0; k<tam_pob; k++){
        for(int i=0; i<dim; i++){
        elem_generado=dist(gen);
        v.push_back(elem_generado);
        }
        poblacion.push_back(v);
        v.clear();
    }
    return poblacion;
}

void Evaluacion(std::vector<std::vector<double>> & poblacion, std::vector<double> & solucion, double &fitness);

void Seleccion(std::vector<std::vector<double>> & poblacion,std::vector<std::vector<double>> & seleccion);

void Cruce(std::vector<std::vector<double>> & seleccion,int tipo, double alpha,double pc,std::vector<std::vector<double>> & cruce);

void Mutacion(std::vector<std::vector<double>> & cruce, double pm,std::vector<std::vector<double>> & mutacion);

void AlgoritmoGeneticoGeneracional(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w,int tam_pob,int semilla){
    srand(semilla); //establecemos semilla
    std::vector<std::vector<double>> poblacion,seleccion,cruce,mutacion;
    std::vector<double>solucion;
    int evaluaciones=0;
    double fitness = 0.0;
    int dim=datos[0].first.size();
    int t=0;

    poblacion=Inicializar(dim,tam_pob);

    for(int k=0; k<tam_pob; k++){
        std::cout << "\nElemento: " << k << std::endl;
        for(int i=0; i<dim; i++){
            std::cout << poblacion[i] [k] << " ";
        }
    }

    /*
    Evaluacion(poblacion,solucion,fitness);
    while(evaluaciones<15000){
        Seleccion(poblacion,seleccion);
        Cruce(seleccion,tipo,0.3,0.7,cruce);
        Mutacion(cruce,0.7,mutacion);
        Reemplazar(poblacion,seleccion,mutacion);
        Evaluacion(poblacion,solucion,fitness);
    }
    */
}

