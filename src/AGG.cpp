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

void Evaluacion(std::vector<std::vector<double>> & poblacion,std::vector<std::pair<std::vector<double>,std::string>> &datos, std::vector<double> & solucion, double &fitness){
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

//TODO Está mal hecho, es con torneo binario
void Seleccion(std::vector<std::vector<double>> & poblacion,std::vector<std::vector<double>> & seleccion,std::mt19937 &generator){
    int tam=poblacion.size();
    for (int i=0; i<tam; i++){
        seleccion.push_back(poblacion[generator()%tam]);
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


void Cruce(std::vector<std::vector<double>> const & seleccion,int tipo, double alpha,double pc,std::vector<std::vector<double>> & cruce,std::mt19937 &generator){
    //Metodo BLX-0.3
    if(tipo==1){
        int dim=seleccion.size();
        int cruces=pc*dim/2; //Numero de parejas que cruzan
        int contador_cruces=0;
        std::cout << "NUM PAREJAS QUE CRUZAN: " << cruces << std::endl;
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

void AlgoritmoGeneticoGeneracional(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double>&w,int tam_pob,int semilla){
    srand(semilla); //establecemos semilla
    std::mt19937 gen(semilla); //generador
    std::vector<std::vector<double>> poblacion,seleccion,cruce;
    std::vector<double>solucion;
    int evaluaciones=0;
    double fitness = 0.0;
    int dim=datos[0].first.size();
    int t=0;

    poblacion=Inicializar(tam_pob,dim,gen);
    /*
    for(int k=0; k<tam_pob; k++){
        std::cout << "\nElemento: " << k << std::endl;
        for(int i=0; i<dim; i++){
            std::cout << poblacion[k][i]  << " ";
        }
    }
    std::cout<<std::endl;
    */

    Evaluacion(poblacion,datos,solucion,fitness);

    /*
    for(int k=0; k<tam_pob; k++){
            std::cout << "\nElemento: " << k << std::endl;
            for(int i=0; i<dim; i++){
                std::cout << poblacion[i] [k] << " ";
            }
        }
    std::cout<<std::endl;

    std::cout<<"Solucion por ahora: " << std::endl;
    for (int i=0; i<dim; i++){
        std::cout << solucion[i] << " ";

    }
    std::cout<<std::endl;
    */
    Seleccion(poblacion,seleccion,gen);
    Cruce(seleccion,1,0.3,0.7,cruce,gen);
    Mutacion(cruce,0.7,gen);
    //TODO ME HE QUEDADO AQUÍ
    Reemplazar(poblacion,seleccion);

    /*
    while(evaluaciones<15000){
        Seleccion(poblacion,seleccion,gen);
        Cruce(seleccion,tipo,0.3,0.7,cruce,gen);
        Mutacion(cruce,0.7,gen);
        Reemplazar(poblacion,seleccion,mutacion);
        Evaluacion(poblacion,solucion,fitness);
    }
    */
}

