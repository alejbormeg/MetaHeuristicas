
#ifndef FUNCIONES
#define FUNCIONES
#include <algorithm>    // std::random_shuffle
#include <cstdlib>      // std::rand, std::srand
#include <utilidades.h>
using namespace std;

template <typename T>
vector<double> distanciaEnemigoMascercano(vector<pair<vector<double>,T>> &entrenamiento, int elemento){
	vector<double> distancia_elem_elem;
	int enemigo_mas_cercano=0;
	double distancia=0;
	double distancia_min=numeric_limits<double>::infinity(); //la ponemos a infinito
	for(int i=0; i<entrenamiento.size();i++){
		if(i!=elemento && entrenamiento[i].second!=entrenamiento[elemento].second){
			distancia=distanciaEuclidea(entrenamiento[i].first,entrenamiento[elemento].first);
			if(distancia<distancia_min){
				distancia_min=distancia;
				enemigo_mas_cercano=i;
			}
		}
	}

	for(int i=0; i<entrenamiento[0].first.size();i++){
		distancia_elem_elem.push_back(abs(entrenamiento[enemigo_mas_cercano].first[i]-entrenamiento[elemento].first[i]));
	}
	return distancia_elem_elem;
}

template <typename T>
vector<double> distanciaAmigoMasCercano(vector<pair<vector<double>,T>> &entrenamiento, int elemento){
	vector<double> distancia_elem_elem;
	int amigo_mas_cercano=0;
	double distancia=0;
	double distancia_min=numeric_limits<double>::infinity(); //la ponemos a infinito
	for(int i=0; i<entrenamiento.size();i++){
		if(i!=elemento && entrenamiento[i].second==entrenamiento[elemento].second){
			distancia=distanciaEuclidea(entrenamiento[i].first,entrenamiento[elemento].first);
			if(distancia<distancia_min){
				distancia_min=distancia;
				amigo_mas_cercano=i;
			}
		}
	}

	for(int i=0; i<entrenamiento[0].first.size();i++){
		distancia_elem_elem.push_back(abs(entrenamiento[amigo_mas_cercano].first[i]-entrenamiento[elemento].first[i]));
	}
	return distancia_elem_elem;
}


template <typename T>
vector<double> metodoRELIEF(vector<pair<vector<double>,T>> &entrenamiento){
	vector<double> w; 
	vector<double> distancias_enemigo; 
	vector<double> distancias_amigo; 

	//Inicializamos w a 0
	for(int i=0; i<entrenamiento[0].first.size();i++){
		w.push_back(0.0);
	}

	//Comenzamos el algoritmo

	for(int i=0; i<entrenamiento.size(); i++){
		distancias_enemigo=distanciaEnemigoMascercano(entrenamiento,i);
		distancias_amigo=distanciaAmigoMasCercano(entrenamiento,i);
		w=w+distancias_enemigo-distancias_amigo;
	}

	double max=*max_element(w.begin(),w.end());

	for(int i=0; i<w.size(); i++){
		if(w[i]<0){
			w[i]=0.0;
		}else{
			w[i]=w[i]/max;
		}
	}
	return w;
}

#endif