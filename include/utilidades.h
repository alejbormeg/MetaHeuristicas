
#ifndef UTILIDADES
#define UTILIDADES

#include <algorithm>    // std::random_shuffle
#include <cassert>
#include<cmath>
#include <vector>
#include <iostream>

double distanciaEuclidea(std::vector<double> &e1, std::vector<double> &e2);

double distanciaPonderada(std::vector<double> &e1, std::vector<double> &e2, std::vector<double> &w);

double tasa_red (std::vector<double>&w);

double funcionEvaluacion(double tasa_clas, double tasa_red);


template <typename T>
void Normalizar( std::vector<std::pair<std::vector<double>,T>> &datos){
	double min;
	double max;

	for(int i=0; i<datos[0].first.size(); i++){
		min=datos[0].first[i];
		max=0.0;
		for (int j=0; j<datos.size(); j++){
			if(datos[j].first[i]>max){
				max=datos[j].first[i];
			}

			if(datos[j].first[i]<min){
				min=datos[j].first[i];
			}
		}

		for (int j=0; j<datos.size(); j++){
			if(max-min!=0)
				datos[j].first[i]=double(datos[j].first[i]-min)/(max-min);
		}

	}
}

template <typename T>
std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b)
{
    assert(a.size() == b.size());

    std::vector<T> result;

    for(int i=0; i<a.size(); i++){
		result.push_back(a[i]+b[i]);
	}

    return result;
}

template <typename T>
std::vector<T> operator-(const std::vector<T>& a, const std::vector<T>& b)
{
    assert(a.size() == b.size());

    std::vector<T> result;

    for(int i=0; i<a.size(); i++){
		result.push_back(a[i]-b[i]);
	}

    return result;
}

template <typename T>
T Clasificador1NN( std::vector<std::pair<std::vector<double>,T>> &datos, std::vector<double> &nuevo_ejemplo,std::vector<double> &w, int posicion=-1) {
	T cmin;
	double dmin;
	if(posicion==0){
		dmin=distanciaPonderada(datos[1].first,nuevo_ejemplo,w);
		cmin=datos[1].second;
	}else{
		dmin=distanciaPonderada(datos[0].first,nuevo_ejemplo,w);
		cmin=datos[0].second;
	}
	
	double distancia=0;

	for (int i=1; i<datos.size(); i++){
		if(i!=posicion){
			distancia=distanciaPonderada(datos[i].first,nuevo_ejemplo,w);
			if(distancia < dmin){
				dmin=distancia;
				cmin=datos[i].second;
			}
		}
	}

	return cmin;
}


template <typename T>
std::vector<std::pair<std::vector<double>,T>> preparaDatos(std::vector<std::pair<std::vector<double>,T>>a, int j){
	std::vector<std::pair<std::vector<double>,T>> b;

	for (int i=0; i<a.size();i++){
		if(i!=j){
			b.push_back(a[i]);
		}
	}

	return b;
}

template <typename T>
double LeaveOneOut (std::vector<std::pair<std::vector<double>,T>> &entrenamiento, std::vector<double> &w){
	int num_elementos=entrenamiento.size();
	int num_correctos=0;
	T etiqueta_predicha;
	std::vector<std::pair<std::vector<double>,T>> one_out;

	for (int i=0; i<entrenamiento.size(); i++){

		etiqueta_predicha=Clasificador1NN(entrenamiento,entrenamiento[i].first,w,i);
		if(etiqueta_predicha==entrenamiento[i].second){
			num_correctos++;
		}
	}
	return 100*((double)(num_correctos)/num_elementos);
}

template <typename T>
double Evaluacion (std::vector<std::pair<std::vector<double>,T>> &entrenamiento,std::vector<std::pair<std::vector<double>,T>> &validacion, std::vector<double> &w){
	int num_correctos=0;
	int num_elementos=validacion.size();
	T etiqueta_predicha;

	for(int i=0; i<validacion.size();i++){
		etiqueta_predicha=Clasificador1NN(entrenamiento,validacion[i].first,w);
		if(etiqueta_predicha==validacion[i].second){
			num_correctos++;
		}
	}	

	return 100*((double)(num_correctos)/num_elementos);
}

//El std::vector datos ya debe venir mezclado, prepara para entrenar con 80% y dejar 20% validacion
template <typename T>
void Prepara5FoldCrossVal(std::vector<std::pair<std::vector<double>,T>> & datos,std::vector<std::pair<std::vector<double>,T>> & entrenamiento,std::vector<std::pair<std::vector<double>,T>> & validacion,int k){
	entrenamiento.clear();
	validacion.clear();
	int num_elem=(int)(datos.size()/5);
	if (k<5){
		bool copia_validacion=false;
		for(int i=0; i<datos.size(); i++){
			if(i==k*num_elem)
				copia_validacion=false;
			if(i==(k-1)*num_elem || copia_validacion){
				copia_validacion=true;
				validacion.push_back(datos[i]);
			}else{
				entrenamiento.push_back(datos[i]);
			}

		}
	}else{
		for (int i=0; i<datos.size() && i!=4*num_elem;i++){
			entrenamiento.push_back(datos[i]);
		}

		for (int i=4*num_elem; i<datos.size();i++){
			validacion.push_back(datos[i]);
		}
	}
}

#endif