#include "../include/AM.h"
#include <algorithm>
#include <cstdlib>




std::vector<int> CalculaMejores(std::vector<double> vfitness, int n){
    double elem=0.0;
    std::vector<int> posiciones;
    std::vector<double>vfitness_ordenado;
    vfitness_ordenado=vfitness;
    //Tenemos los valores ordenados
    std::sort(vfitness_ordenado.begin(),vfitness_ordenado.end());

    for(int i=0; i<n; i++){
        //Buscamos el i-esimo máximo
        elem=vfitness_ordenado[vfitness_ordenado.size()-i-1]; //Elemento que buscamos
        for(int j=0; j<vfitness.size(); j++){
            if(vfitness[j]==elem){
                //Nos quedamos con su posición
                posiciones.push_back(j);
            }
        }
    }

    return posiciones;
}

void ReemplazarYEvaluarAM(std::vector<std::vector<double>> & poblacion,std::vector<std::vector<double>> const & mutaciones,std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double> & w,double &fitness, std::vector<double> & vfitness){
    double fitness1=0.0, minimofitness=100.0,maximofitness=0.0;
    double tasa_clas=0.0, tasa_red_=0.0;
    int indice_peor=0,indice_mejor=0;
    std::vector<double> v;

    //Limpiamos la población anterior
    poblacion.clear();

    //Evaluamos todos los vectores de la nueva población
    for(int i=0; i<mutaciones.size();i++){
        v=mutaciones[i];
        //Calculamos el valor de fitness de v1
        tasa_clas=LeaveOneOut(datos,v);
        tasa_red_=tasa_red(v);
        fitness1=funcionEvaluacion(tasa_clas,tasa_red_);
        if(fitness1<minimofitness){
            indice_peor=i;
            minimofitness=fitness1;
        }

        if(fitness1>maximofitness){
            indice_mejor=i;
            maximofitness=fitness1;
        }

        vfitness.push_back(fitness1);
    }

    //Si el mínimo es mejor que la solución de la población anterior
    if(minimofitness>fitness){
        //No conservamos el mejor de la anterior   
        poblacion=mutaciones;
    }else{
        //En caso contrario eliminamos el peor de mutaciones y lo reemplazamos si no está
        /*
        if(!Contiene(mutaciones,w)){
            poblacion=mutaciones;
            poblacion[indice_peor]=w;
        }
        else{
            poblacion=mutaciones;
        }
        */
    }

    if(maximofitness>fitness){
        w=poblacion[indice_mejor];
        fitness=maximofitness;
    }
}

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

void AlgoritmoMemetico(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w,int tam_pob,int semilla,int tipo,double pls, bool mejores, std::mt19937 & gen){
    std::vector<std::vector<double>> poblacion,seleccion,cruce;
    int solucion;
    int evaluaciones=0;
    double fitness = 0.0;
    int dim=datos[0].first.size();
    int t=0; //Contador generaciones 
    //Numero de cromosomas que hacen BL
    int ncromosomas=tam_pob*pls; //Esperanza matematica
    std::vector<double> vfitness;  // guarda los valores de fitness de los elementos de la poblacion
    std::vector<int> pos_mejores;//Guarda las posiciones de los mejores elementos, solo en caso de 0.1*N mejores

    poblacion=Inicializar(tam_pob,dim,gen);
    //Evaluacion(poblacion,datos,solucion,fitness,vfitness);
    w=poblacion[solucion];
    while(evaluaciones<15000){
        Seleccion(datos,poblacion,seleccion,gen,tam_pob,vfitness);
        Cruce(seleccion,tipo,0.3,0.7,cruce,gen);
        Mutacion(cruce,0.1,gen);
        ReemplazarYEvaluarAM(poblacion,cruce,datos,w,fitness,vfitness);
        evaluaciones+=tam_pob;
        t++;
        seleccion.clear();
        cruce.clear();
        
        if(t%10==0){
            t=0;
            if(!mejores){
                for(int i=0; i<ncromosomas;i++){
                    BusquedaLocalAM(datos,poblacion[i],evaluaciones,gen);
                }

            }else{
                pos_mejores=CalculaMejores(vfitness,ncromosomas);
                for(int i=0; i<pos_mejores.size();i++){
                    BusquedaLocalAM(datos,poblacion[pos_mejores[i]],evaluaciones,gen);
                }
            }
        }
        vfitness.clear();
    }
}
