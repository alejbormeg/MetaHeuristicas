
#ifndef FUNCIONES
#define FUNCIONES
#include<vector>
#include<cmath>
#include <algorithm>    // std::random_shuffle
#include <cstdlib>      // std::rand, std::srand
#include <cassert>
using namespace std;

template <typename T>
vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b)
{
    assert(a.size() == b.size());

    vector<T> result;

    for(int i=0; i<a.size(); i++){
		result.push_back(a[i]+b[i]);
	}

    return result;
}

template <typename T>
vector<T> operator-(const std::vector<T>& a, const std::vector<T>& b)
{
    assert(a.size() == b.size());

    vector<T> result;

    for(int i=0; i<a.size(); i++){
		result.push_back(a[i]-b[i]);
	}

    return result;
}

double distanciaEuclidea(vector<double> &e1, vector<double> &e2);

double distanciaPonderada(vector<double> &e1, vector<double> &e2, vector<double> &w);

template <typename T>
T Clasificador1NN( vector<pair<vector<double>,T>> &datos, vector<double> nuevo_ejemplo,vector<double> w) {
	T cmin=datos[0].second;
	double dmin=distanciaEuclidea(datos[0].first,nuevo_ejemplo);
	double distancia=0;

	for (int i=1; i<datos.size(); i++){
		distancia=distanciaPonderada(datos[i].first,nuevo_ejemplo,w);
		if(distancia < dmin){
			dmin=distancia;
			cmin=datos[i].second;
		}
	}

	return cmin;
}

double tasa_red (vector<double>&w);

double funcionEvaluacion(double tasa_clas, double tasa_red);

template <typename T>
vector<pair<vector<double>,T>> preparaDatos(vector<pair<vector<double>,T>>a, int j){
	vector<pair<vector<double>,T>> b;

	for (int i=0; i<a.size();i++){
		if(i!=j){
			b.push_back(a[i]);
		}
	}

	return b;
}

template <typename T>
double LeaveOneOut (vector<pair<vector<double>,T>> entrenamiento, vector<double> &w){
	int num_elementos=entrenamiento.size();
	int num_correctos=0;
	T etiqueta_predicha;
	vector<pair<vector<double>,T>> one_out;

	for (int i=0; i<entrenamiento.size(); i++){
		one_out=preparaDatos(entrenamiento,i);
		etiqueta_predicha=Clasificador1NN(one_out,entrenamiento[i].first,w);
		if(etiqueta_predicha==entrenamiento[i].second){
			num_correctos++;
		}
	}

	return 100*((double)(num_correctos)/num_elementos);
}

//El vector datos ya debe venir mezclado, prepara para entrenar con 80% y dejar 20% validacion
template <typename T>
void Prepara5FoldCrossVal(vector<pair<vector<double>,T>> & datos,vector<pair<vector<double>,T>> & entrenamiento,vector<pair<vector<double>,T>> & validacion,int k){
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