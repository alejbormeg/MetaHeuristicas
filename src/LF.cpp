#include "../include/LF.h"
#include <cstdlib>


std::vector<double> create_trial(std::vector<double> &leader, std::vector<double> &follower, std::mt19937 &generator){
  std::vector<double> trial;
  std::uniform_real_distribution<> dis(0.0, 1.0);
  double epsilon,valor;
  for (int i=0; i<leader.size(); i++){
    epsilon=dis(generator);
    valor=follower[i]+epsilon*2*(leader[i]-follower[i]);
    if(valor<0)
      trial.push_back(0.0);
    else if(valor>1.0)
      trial.push_back(1.0);
    else 
      trial.push_back(valor);
  }
  return trial;
}

double CalcMHWScore(std::vector<double> scores)
{
  size_t size = scores.size();
  if (size == 0)
  {
    return 0;  // Undefined, really.
  }
  else
  {
    sort(scores.begin(), scores.end());
    if (size % 2 == 0)
    {
      return (scores[size / 2 - 1] + scores[size / 2]) / 2;
    }
    else 
    {
      return scores[size / 2];
    }
  }
}

std::vector<std::vector<double>> merge_populations(std::vector<std::vector<double>> &L, std::vector<std::vector<double>> &F,std::vector<double> &l_fitness,std::vector<double> &f_fitness, std::mt19937 &generator){
  std::vector<std::vector<double>> Nuevos_Lideres;
  //en primer lugar, guardamos la mejor solución de Líderes
  int maxElementIndex = std::max_element(l_fitness.begin(),l_fitness.end()) - l_fitness.begin();
  Nuevos_Lideres.push_back(L[maxElementIndex]);
  //Seleccionamos los siguientes n-1 con torneo binario
  for (int i=0; i<L.size(); i++){
    if(i!=maxElementIndex){
      if(l_fitness[i]>f_fitness[i])
        Nuevos_Lideres.push_back(L[i]);
      else 
        Nuevos_Lideres.push_back(F[i]);
    }
  }
  L=Nuevos_Lideres;
  return L;
}

void LeadersAndFollowers(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double> &sol, int maxevals, int tam_pob, int dim, std::mt19937 &generator){
  std::vector<std::vector<double>> L,F;
  std::vector<double> l_fitness,f_fitness;
  std::vector<double> leader,follower,trial;
  double tasa_clas, tasa_red_,fitness1,fitness2;
  L=Inicializar(tam_pob,dim,generator);
  F=Inicializar(tam_pob,dim,generator);
  int evals=0;
  
  while(evals<maxevals){
    std::cout << "evals:  "<< evals << std::endl;
    for(int i=0; i<tam_pob ; i++){
      leader=L[i];
      follower=F[i];
      trial=create_trial(leader,follower,generator);
      tasa_clas=LeaveOneOut(datos,trial);
      tasa_red_=tasa_red(trial);
      fitness1=funcionEvaluacion(tasa_clas,tasa_red_);
      tasa_clas=LeaveOneOut(datos,follower);
      tasa_red_=tasa_red(follower);
      fitness2=funcionEvaluacion(tasa_clas,tasa_red_);
      if(fitness1>fitness2){
        F[i]=trial;
        f_fitness.push_back(fitness1);
      } else {
        f_fitness.push_back(fitness2);
      }
    }
    
    //Calculamos el std::vector de Fitness de cada poblacion
    for(int i=0;i<L.size();i++){
      tasa_clas=LeaveOneOut(datos,L[i]);
      tasa_red_=tasa_red(L[i]);
      fitness1=funcionEvaluacion(tasa_clas,tasa_red_);
      l_fitness.push_back(fitness1);
    }

    if(CalcMHWScore(f_fitness)>CalcMHWScore(l_fitness)){
      L=merge_populations(L,F,l_fitness,f_fitness,generator);
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