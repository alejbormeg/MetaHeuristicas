#include "../include/LFBL.h"
#include <cstdlib>

void LeadersAndFollowersLocalSearch(std::vector<std::pair<std::vector<double>,std::string>> &datos,std::vector<double> &sol, int maxevals, int tam_pob, int dim, std::mt19937 &generator){
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
    
    //Calculamos el std::vector de Fitness de líderes
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
  
  //Realizamos BL

  std::vector<int> mejores=CalculaMejores(l_fitness,1);
  std::vector<double> v;
  v=L[mejores[0]];
  BusquedaLocal(datos,v,generator,dim,10000);
  sol=v;

}