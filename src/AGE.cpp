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

void CalculaFitness(std::vector<std::vector<double>> & poblacion,std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&vfitness,int &pos_mejor, int &pos_peor, int &pos_segundo_peor){
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
    //Hacemos que el peor ya no sea el peor momentáneamente, para así calcular el segundo peor
    vfitness[pos_peor]=vfitness[pos_peor]+100.0;
    //Calculamos el segundo peor, que ahora es el peor
    pos_segundo_peor=CalculaPeor(vfitness);
    //Restauramos el valor del peor
    vfitness[pos_peor]=vfitness[pos_peor]-100.0;
}

void ReemplazamientoCompetitivo (std::vector<std::vector<double>> & poblacion,std::vector<std::vector<double>> & mutaciones,std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double> & vfitness, int &pos_mejor, int &pos_peor, int &pos_segundo_peor){
    double fitness1=0.0,fitness2=0.0, minimofitness=100.0;
    double tasa_clas=0.0, tasa_red_=0.0;
    std::vector<double> v;

    //TODO REVISAR Y REPENSAR
    v=mutaciones[0];
    tasa_clas=LeaveOneOut(datos,v);
    tasa_red_=tasa_red(v);
    fitness1=funcionEvaluacion(tasa_clas,tasa_red_);
    if(vfitness[pos_segundo_peor]<fitness1){
        vfitness[pos_segundo_peor]=fitness1;
        poblacion[pos_segundo_peor]=v;
        //Comprobamos si es el nuevo mejor
        if(vfitness[pos_mejor]<fitness1){
            pos_mejor=pos_segundo_peor;
        }
        //Calculamos el nuevo segundo peor
        vfitness[pos_peor]=vfitness[pos_peor]+100.0;
        //Calculamos el segundo peor, que ahora es el peor
        pos_segundo_peor=CalculaPeor(vfitness);
        //Restauramos el valor del peor
        vfitness[pos_peor]=vfitness[pos_peor]-100.0;
    } else if(vfitness[pos_peor]<fitness1){
        vfitness[pos_peor]=fitness1;
        poblacion[pos_peor]=v; //Sigue siendo el peor
    }

    v=mutaciones[1];
    tasa_clas=LeaveOneOut(datos,v);
    tasa_red_=tasa_red(v);
    fitness1=funcionEvaluacion(tasa_clas,tasa_red_);
    if(vfitness[pos_segundo_peor]<fitness1){
        vfitness[pos_segundo_peor]=fitness1;
        poblacion[pos_segundo_peor]=v;
        //Comprobamos si es el nuevo mejor
        if(vfitness[pos_mejor]<fitness1){
            pos_mejor=pos_segundo_peor;
        }
        //Calculamos el nuevo segundo peor
        vfitness[pos_peor]=vfitness[pos_peor]+100.0;
        //Calculamos el segundo peor, que ahora es el peor
        pos_segundo_peor=CalculaPeor(vfitness);
        //Restauramos el valor del peor
        vfitness[pos_peor]=vfitness[pos_peor]-100.0;
    } else if(vfitness[pos_peor]<fitness1){
        vfitness[pos_peor]=fitness1;
        poblacion[pos_peor]=v; //Sigue siendo el peor
    }

}

void AlgoritmoGeneticoEstacionario(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w,int tam_pob,int tipo, std::mt19937 & gen){
    std::vector<std::vector<double>> poblacion,seleccion,cruce;
    int solucion; //índice a la mejor solución de la población
    std::vector<double> vector_fitness; // guarda los valores de fitness de los elementos de la poblacion
    
    int evaluaciones=0;
    int dim=datos[0].first.size();
    int pos_mejor=0;
    int pos_peor=0, pos_segundo_peor=0;

    poblacion=Inicializar(tam_pob,dim,gen);
    CalculaFitness(poblacion,datos,vector_fitness,solucion,pos_peor,pos_segundo_peor);

    while(evaluaciones<15000){
        Seleccion(datos,poblacion,seleccion,gen,2,vector_fitness);
        Cruce(seleccion,tipo,0.3,1,cruce,gen);
        Mutacion(cruce,0.1,gen);
        ReemplazamientoCompetitivo(poblacion,cruce,datos,vector_fitness,solucion,pos_peor,pos_segundo_peor);
        w=poblacion[solucion];

        evaluaciones+=2;
        seleccion.clear();
        cruce.clear();
    }
}
