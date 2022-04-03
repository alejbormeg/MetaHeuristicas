#include"../include/utilidades.h"

double distanciaEuclidea(std::vector<double> &e1, std::vector<double> &e2){
	double distancia;
	double suma=0; 
	double aux=0;

	for(int i=0; i<e1.size(); i++){
		aux=e1[i]-e2[i];
		suma+=aux*aux;
	}

	return sqrt(suma);
}

double distanciaPonderada(std::vector<double> &e1, std::vector<double> &e2, std::vector<double> &w){
	double distancia;
	double suma=0; 
	double aux=0;

	for(int i=0; i<e1.size(); i++){
		aux=(e1[i]-e2[i]);
		suma+=w[i]*aux*aux;
	}

	return sqrt(suma);
}

double tasa_red (std::vector<double>&w){
	int numvalores=0;

	for(int i=0;i<w.size();i++){
		if(w[i]<0.1){
			numvalores++;
		}
	}
	return 100*((double)(numvalores)/w.size());
}

double funcionEvaluacion(double tasa_clas, double tasa_red){
	return 0.5*tasa_clas+0.5*tasa_red;
}
