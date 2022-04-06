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

void Normalizar( std::vector<std::pair<std::vector<double>,std::string>> &datos){
	double min;
	double max;

	//Para cada atributo
	for(int i=0; i<datos[0].first.size(); i++){
		min=datos[0].first[i];
		max=0.0;
		//Recorremos todos los atributos en columna calculando el máximo y mínimo
		for (int j=0; j<datos.size(); j++){
			if(datos[j].first[i]>max){
				max=datos[j].first[i];
			}

			if(datos[j].first[i]<min){
				min=datos[j].first[i];
			}
		}

		//Normalizamos todos los atributos teniendo en cuenta el max y min
		for (int j=0; j<datos.size(); j++){
			if(max-min!=0)
				datos[j].first[i]=double(datos[j].first[i]-min)/(max-min);
		}

	}
}

std::string Clasificador1NN( std::vector<std::pair<std::vector<double>,std::string>> &datos, std::vector<double> &nuevo_ejemplo,std::vector<double> &w, int posicion) {
	std::string cmin;
	double dmin;
	//Inicializamos 
	if(posicion==0){
		dmin=distanciaPonderada(datos[1].first,nuevo_ejemplo,w);
		cmin=datos[1].second;
	}else{
		dmin=distanciaPonderada(datos[0].first,nuevo_ejemplo,w);
		cmin=datos[0].second;
	}
	
	double distancia=0;

	//Calculamos la distancia ponderada con todos los datos y nos quedamos con la clase del de menor distancia
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

double LeaveOneOut (std::vector<std::pair<std::vector<double>,std::string>> &entrenamiento, std::vector<double> &w){
	int num_elementos=entrenamiento.size();
	int num_correctos=0;
	std::string etiqueta_predicha;

	//Para cada dato de entrenamiento
	for (int i=0; i<entrenamiento.size(); i++){
		//Calculamos su etiqueta sin tenerlo a él en cuenta
		etiqueta_predicha=Clasificador1NN(entrenamiento,entrenamiento[i].first,w,i);
		//Si acierta contamos el acierto
		if(etiqueta_predicha==entrenamiento[i].second){
			num_correctos++;
		}
	}
	return 100*((double)(num_correctos)/num_elementos);
}

void Prepara5FoldCrossVal(std::vector<std::pair<std::vector<double>,std::string>> & datos,std::vector<std::pair<std::vector<double>,std::string>> & entrenamiento,std::vector<std::pair<std::vector<double>,std::string>> & validacion,int k){
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
