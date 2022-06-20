#include "../include/LF.h"
#include <cstdlib>


std::vector<double> create_trial(std::vector<double> &leader, std::vector<double> &follower, std::mt19937 &generator){
  std::vector<double> trial;
  std::uniform_real_distribution<> dis(0.0, 1.0);
  double epsilon,valor;

  for (int i=0; i<leader.size(); i++){
    //Generamos un epsilon aleatorio
    epsilon=dis(generator);
    //Calculamos el valor de la componente actual
    valor=follower[i]+epsilon*2*(leader[i]-follower[i]);
    //Si se pasa de los límites del dominio se ajusta
    if(valor<0)
      trial.push_back(0.0);
    else if(valor>1.0)
      trial.push_back(1.0);
    else 
      trial.push_back(valor);
  }
  //Devolvemos trial
  return trial;
}

double CalcMHWScore(std::vector<double> scores)
{
  //Calculamos tamaño del vector
  size_t size = scores.size();
  if (size == 0)
  {
    return 0;  // Undefined, really.
  }
  else
  {
    //Ordenamos el vector
    sort(scores.begin(), scores.end());
    if (size % 2 == 0)
    {
      //Interpolamos en caso de ser par
      return (scores[size / 2 - 1] + scores[size / 2]) / 2;
    }
    else 
    {
      //Devolvemos el punto medio en caso de ser impar
      return scores[size / 2];
    }
  }
}

std::vector<std::vector<double>> merge_populations(std::vector<std::vector<double>> &L, std::vector<std::vector<double>> &F,std::vector<double> &l_fitness,std::vector<double> &f_fitness, std::mt19937 &generator){
  std::vector<std::vector<double>> Nuevos_Lideres;
  //Seleccionamos los siguientes n-1 con torneo binario
  for (int i=0; i<L.size()-1; i+=2){
    if(l_fitness[i]>l_fitness[i+1])
      Nuevos_Lideres.push_back(L[i]);
    else 
      Nuevos_Lideres.push_back(L[i+1]);

    if(f_fitness[i]>f_fitness[i+1])
      Nuevos_Lideres.push_back(F[i]);
    else
      Nuevos_Lideres.push_back(F[i+1]);
  }
  
  return Nuevos_Lideres;
}

void LeadersAndFollowers(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double> &sol, int maxevals, int tam_pob, int dim, std::mt19937 &generator){
  std::vector<std::vector<double>> L,F;
  std::vector<double> l_fitness,f_fitness;
  std::vector<double> leader,follower,trial;
  double tasa_clas, tasa_red_,fitness1,fitness2;

  //Inicializamos las poblaciones
  L=Inicializar(tam_pob,dim,generator);
  F=Inicializar(tam_pob,dim,generator);
  int evals=0;
  
  //Mientras no se supere el numero maximo de evaluaciones
  while(evals<maxevals){
    std::cout << "evals:  "<< evals << std::endl;
    for(int i=0; i<tam_pob ; i++){
      //Tomamos lider
      leader=L[i];
      //Tomamos seguidor
      follower=F[i];
      //Los combinamos
      trial=create_trial(leader,follower,generator);
      tasa_clas=LeaveOneOut(datos,trial);
      tasa_red_=tasa_red(trial);
      fitness1=funcionEvaluacion(tasa_clas,tasa_red_);
      tasa_clas=LeaveOneOut(datos,follower);
      tasa_red_=tasa_red(follower);
      fitness2=funcionEvaluacion(tasa_clas,tasa_red_);
      //Si la combinacion es mejor que el seguidor, lo reemplaza
      if(fitness1>fitness2){
        F[i]=trial;
        f_fitness.push_back(fitness1);
      } else {
        f_fitness.push_back(fitness2);
      }
    }
    
    //Calculamos el vector de Fitness de cada poblacion
    for(int i=0;i<L.size();i++){
      tasa_clas=LeaveOneOut(datos,L[i]);
      tasa_red_=tasa_red(L[i]);
      fitness1=funcionEvaluacion(tasa_clas,tasa_red_);
      l_fitness.push_back(fitness1);
    }

    //Si la mediana de los seguidores es mayor que la de los líderes, se mezclan
    if(CalcMHWScore(f_fitness)>CalcMHWScore(l_fitness)){
      //mezclamos poblaciones
      L=merge_populations(L,F,l_fitness,f_fitness,generator);
      //Inicializamos de nuevo la población de los seguidores
      F=Inicializar(tam_pob,dim,generator);
    }
    
    f_fitness.clear();
    l_fitness.clear();
    evals+=2*tam_pob;
  }

  //Obtenemos la mejor solución
  for(int i=0;i<L.size();i++){
    tasa_clas=LeaveOneOut(datos,F[i]);
    tasa_red_=tasa_red(F[i]);
    fitness1=funcionEvaluacion(tasa_clas,tasa_red_);
    l_fitness.push_back(fitness1);
  }
  //obtenemos el mínimo fitness
  int maxElementIndex = std::max_element(l_fitness.begin(),l_fitness.end()) - l_fitness.begin();
  sol=L[maxElementIndex];
}