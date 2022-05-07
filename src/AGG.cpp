#include "../include/AGG.h"
#include <cstdlib>

std::vector<std::vector<double>> Inicializar(int tam_pob, int dim, std::mt19937 &generator){
    std::vector<double> v;
    std::vector<std::vector<double>> poblacion;
    // Will be used to obtain a seed for the random number engine
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double elem_generado;

    //Generamos tantos vectores como indique tam_pob
    for(int k=0; k<tam_pob; k++){
        for(int i=0; i<dim; i++){
            elem_generado=dist(generator);
            v.push_back(elem_generado);
        }
        poblacion.push_back(v);
        v.clear();
    }
    return poblacion;
}

void Evaluacion(std::vector<std::vector<double>> const & poblacion,std::vector<std::pair<std::vector<double>,std::string>> &datos, std::vector<double> & solucion, double &fitness){
    double actual_fitness=0.0;
    double tasa_clas=0.0, tasa_red_=0.0;
    std::vector<double> sol_actual;

    //Cada cromosoma se evalúa y tomamos como solución el mejor de l población 
    for (int i=0; i<poblacion.size(); i++){
        sol_actual=poblacion[i];
        tasa_clas=LeaveOneOut(datos,sol_actual);
        tasa_red_=tasa_red(sol_actual);
        actual_fitness=funcionEvaluacion(tasa_clas,tasa_red_);
        if(actual_fitness>fitness){
            solucion=sol_actual;
            fitness=actual_fitness;
        }
    }
}

void Seleccion(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<std::vector<double>> const & poblacion,std::vector<std::vector<double>> & seleccion,std::mt19937 &generator,int tam){
    double fitness1=0.0, fitness2=0.0;
    double tasa_clas=0.0, tasa_red_=0.0;
    std::vector<double> v1,v2;
    for (int i=0; i<tam; i++){
        v1=poblacion[generator()%tam];
        v2=poblacion[generator()%tam];
        //Calculamos el valor de fitness de v1
        tasa_clas=LeaveOneOut(datos,v1);
        tasa_red_=tasa_red(v1);
        fitness1=funcionEvaluacion(tasa_clas,tasa_red_);
        //Calculamos el valor de fitness de v2
        tasa_clas=LeaveOneOut(datos,v2);
        tasa_red_=tasa_red(v2);
        fitness2=funcionEvaluacion(tasa_clas,tasa_red_);

        if(fitness1>fitness2)
            seleccion.push_back(v1);
        else
            seleccion.push_back(v2);
    }
}

void BLX(std::vector<double> const & c1,std::vector<double>const &  c2,std::vector<std::vector<double>> & cruce, double alpha,std::mt19937 &generator){
    std::vector<double>maximos,minimos;

    maximos.push_back(*std::max_element(c1.begin(), c1.end()));
    maximos.push_back(*std::max_element(c2.begin(), c2.end()));
    minimos.push_back(*std::min_element(c1.begin(), c1.end()));
    minimos.push_back(*std::min_element(c2.begin(), c2.end()));

    //cmax
    double max=*std::max_element(maximos.begin(),maximos.end());
    //cmin
    double min=*std::min_element(minimos.begin(),minimos.end());
    //l*alpha
    double constante=(max-min)*alpha;

    //Tomamos los elementos de una uniforme con el intervalo deseado
    std::uniform_real_distribution<double> dist(min-constante, max+constante);
    
    //Hijos generados
    std::vector<double>h;

    //variables auxiliares
    double elem_generado;

    for(int k=0; k<2; k++){
        for(int i=0; i<c1.size(); i++){
            elem_generado=dist(generator);
            if(elem_generado>1.0)
                elem_generado=1.0;
            else if(elem_generado<0.0)
                elem_generado=0.0;
            h.push_back(elem_generado);
        }
        cruce.push_back(h);
        h.clear();
    }

}

void ARITMETICO(std::vector<double> const &c1,std::vector<double> const &c2,std::vector<std::vector<double>> & cruce,std::mt19937 &generator){
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double alpha=0.0;
    double elemento=0.0;
    //Hijos generados
    std::vector<double>h;

    for(int k=0; k<2; k++){
        alpha=dist(generator);

        for(int i=0; i<c1.size(); i++){
            elemento=((alpha*c1[i])+(1-alpha)*c2[i]);
            if(elemento>1.0)
                elemento=1.0;
            else if(elemento<0.0)
                elemento=0.0;
            h.push_back(elemento);
        }
        cruce.push_back(h);
        h.clear();
    }

}



void Cruce(std::vector<std::vector<double>> const & seleccion,int tipo, double alpha,double pc,std::vector<std::vector<double>> & cruce,std::mt19937 &generator){
    int dim=seleccion.size();
    int cruces=pc*dim/2; //Numero de parejas que cruzan
    int contador_cruces=0;
    //Metodo BLX-0.3
    if(tipo==1){
        //Las parejas son (1,2), (2,3) ... (n-1,n)
        for (int i=0; i<dim; i+=2){
            if (contador_cruces<cruces)
                BLX(seleccion[i],seleccion[i+1],cruce,alpha,generator);
            else{
                cruce.push_back(seleccion[i]);
                cruce.push_back(seleccion[i+1]);
            }   
        }
        //Si tenía longitud impar el último queda sin pareja y se añade al final
        if(dim%2!=0){
            cruce.push_back(seleccion[dim-1]);
        }

    //Cruce aritmético
    }else if(tipo==2){
        //Las parejas son (1,2), (2,3) ... (n-1,n)
        for (int i=0; i<dim; i+=2){
            if (contador_cruces<cruces)
                ARITMETICO(seleccion[i],seleccion[i+1],cruce,generator);
            else{
                cruce.push_back(seleccion[i]);
                cruce.push_back(seleccion[i+1]);
            }   
        }
        //Si tenía longitud impar el último queda sin pareja y se añade al final
        if(dim%2!=0){
            cruce.push_back(seleccion[dim-1]);
        }
    }
}

void Mov(std::vector<double> & w, double sigma, int pos,std::mt19937 &generator){
    //Se inicializa con la desviación estandar, por eso usamos sigma en lugar de sigma²
    std::normal_distribution<double> dist(0.0,sigma);
    double z=dist(generator);
    //Mutamos el gen correspondiente
    w[pos]=w[pos]+z;

    //Nos aseguramos que está entre 0.0 y 1.0 el valor final
    if(w[pos]>1.0){
        w[pos]=1.0;
    }

    if(w[pos]<0.0){
        w[pos]=0.0;
    }

}

void Mutacion(std::vector<std::vector<double>> & cruce, double pm,std::mt19937 &generator){
    int num_cromosomas=cruce.size();
    int genes=cruce[0].size();
    //De acuerdo con las recomendaciones mutan Pm*numgenes
    int num_mutaciones=pm*num_cromosomas*genes;

    //Coordenadas de la matriz a mutar
    int fila,col;
    //Las mutaciones se hacen sobre los cruces anteriores
    for(int i=0; i<num_mutaciones; i++){
        fila=generator()%num_cromosomas;
        col=generator()%genes;
        Mov(cruce[fila],0.3,col,generator);
    }
}


bool Contiene(std::vector<std::vector<double>>const & poblacion,std::vector<double> & w){
    int coincidencias=0, dim=w.size();
    for(int i=0; i<poblacion.size(); i++){
        for(int j=0; j<dim; j++){
            if(poblacion[i][j]==w[j]){
                coincidencias++;
            }else 
                break;
        }
        if(coincidencias==dim)
            return true; 
        else 
            coincidencias=0;
    }

    return false;

}

void ReemplazarYEvaluar(std::vector<std::vector<double>> & poblacion,std::vector<std::vector<double>> & mutaciones,std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double> & w,double &fitness){
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
    }

    //Si el mínimo es mejor que la solución de la población anterior
    if(minimofitness>fitness){
        //No conservamos el mejor de la anterior   
        poblacion=mutaciones;
    }else{
        //En caso contrario eliminamos el peor de mutaciones y lo reemplazamos si no está
        if(!Contiene(mutaciones,w)){
            poblacion=mutaciones;
            poblacion[indice_peor]=w;
        }
        else{
            poblacion=mutaciones;
        }
    }

    if(maximofitness>fitness){
        w=poblacion[indice_mejor];
        fitness=maximofitness;
    }
}


void AlgoritmoGeneticoGeneracional(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w,int tam_pob,int semilla,int tipo){
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
        Seleccion(datos,poblacion,seleccion,gen,tam_pob);
        Cruce(seleccion,tipo,0.3,0.7,cruce,gen);
        Mutacion(cruce,0.1,gen);
        ReemplazarYEvaluar(poblacion,cruce,datos,solucion,fitness);
        //Evaluacion(poblacion,datos,solucion,fitness);
        evaluaciones+=30;
        seleccion.clear();
        cruce.clear();
    }
    w=solucion;
}

