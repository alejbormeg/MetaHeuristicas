#include "../include/AM.h"
#include <cstdlib>




void BusquedaLocalAM(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w, int &contador_evaluaciones, std::mt19937 &generator){
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
    int contador_mut=0; //contador de número de mutaciones

    while(contador_mut<(2*tam_vector)){
        std::random_shuffle(orden_mutaciones.begin(),orden_mutaciones.end());
        mejora=false;
        for(int i=0; i<tam_vector && mejora==false; i++){
            w_mutado=w;
            Mov(w_mutado,0.3,orden_mutaciones[i],generator);
            contador_mut++; //aumentamos el número de vecinos
            tasa_clas=LeaveOneOut(datos,w_mutado);

            tasa_red_=tasa_red(w_mutado);

            funcion_evaluacion=funcionEvaluacion(tasa_clas,tasa_red_);
            contador_evaluaciones++; //aumentamos el número de evaluaciones de la funcion objetivo
            if(funcion_evaluacion>fmax){
                fmax=funcion_evaluacion;
                w=w_mutado;
                mejora=true;
                contador_mut=0;
            }
            
        }
        //Salimos
    }
}

void AlgoritmoMemetico(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w,int tam_pob,int semilla,int tipo,double pls){
    srand(semilla); //establecemos semilla
    std::mt19937 gen(semilla); //generador
    std::vector<std::vector<double>> poblacion,seleccion,cruce;
    std::vector<double>solucion;
    int evaluaciones=0;
    double fitness = 0.0;
    int dim=datos[0].first.size();
    int t=0; //Contador generaciones 
    //Numero de cromosomas que hacen BL
    int ncromosomas=poblacion.size()*pls; //Esperanza matematica

    poblacion=Inicializar(tam_pob,dim,gen);
    Evaluacion(poblacion,datos,solucion,fitness);
    
    while(evaluaciones<15000){
        Seleccion(datos,poblacion,seleccion,gen,tam_pob);
        Cruce(seleccion,tipo,0.3,0.7,cruce,gen);
        Mutacion(cruce,0.1,gen);
        ReemplazarYEvaluar(poblacion,cruce,datos,solucion,fitness);
        evaluaciones+=30;
        t++;
        seleccion.clear();
        cruce.clear();
        if(t%10==0){
            t=0;
            for(int i=0; i<ncromosomas;i++){
                BusquedaLocalAM(datos,poblacion[i],evaluaciones,gen);
            }
        }
    }
    w=solucion;   
}
