#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "../include/utilidades.h"
#include "../include/RELIEF.h"
#include "../include/BL.h"
#include <ctime> 


using namespace std;

ifstream infile;
ofstream outfile;
//Variables para la lectura de datos
string ionosphere="Instancias_APC/ionosphere.arff";
string parkinsons="Instancias_APC/parkinsons.arff";
string spectf_heart="Instancias_APC/spectf-heart.arff";

/**
 * @brief Función para abrir el fichero de lectura
 * 
 * @param infile Variable para abrir el fichero de lectura
 * @param filename Nombre del fichero
 */
void openFiles (ifstream& infile, string filename){
	infile.open(filename);
		if (!infile)
		{
			cout << "Cannot open the input file. Program terminates!"<< endl;
		}
}

/**
 * @brief Función para leer el flujo de datos del fichero de entrada. Usaremos una estructura del tipo vector de parejas vector-etiqueta.
 * 
 * @param infile flujo de entrada
 * @param datos vector dónde almacenamos los datos
 */
void readData(ifstream &infile, vector<pair<vector<double>,string>> &datos){
	string text_line;
	vector <double> row;
	string etiqueta;

 	while (getline(infile, text_line)){
		// Check the line length first.  Empty lines are ignored.
		if (text_line.length() == 0)
		{
			continue;
		}
		// Test lines for rejection by reading the first character.
		const char c = text_line[0];
		if ((c == '@') || (c == '%') || (c == ' '))
		{
			continue;
		}
		
		stringstream ss(text_line);
		while (ss.good()){
			string substr;
			getline(ss, substr, ',');

			if (substr[0]=='g' or substr[0]=='b'){
				etiqueta=substr;
			} else{
				row.push_back(stof(substr));
			}		
			
		}

		if(etiqueta=="g" || etiqueta=="b"){
			datos.push_back(make_pair(row,etiqueta));
		}
		else{
			etiqueta=to_string(row.back());
			row.pop_back();
			datos.push_back(make_pair(row,etiqueta));
		}
		row.clear();
	}
}

int main(int argc, char *argv[])
{	
	//Declaración de variables
	ifstream infile; //Variable de tipo ifstream para leer de fichero
	//La estructura de datos que usaremos será un vector de pares vector-etiqueta
	vector<pair<vector<double>,string>> datos;

	//Variables para separar entre entrenamiento y test en Cross Validation
	vector<pair<vector<double>,string>> entrenamiento;
	vector<pair<vector<double>,string>> validacion;
	//Vector de pesos
	vector<double> w;
	//Variables para recoger estadísticas
	double tasa_clas=0;
	double tasa_red_=0;
	double funcion_evaluacion=0;
	double tasa_clas_promedio=0.0;
	double tasa_red_promedio=0.0;
	double funcion_evaluacion_promedio=0.0;
	unsigned t0,t1;
	double tiempo=0.0;

	//Leemos los datos del fichero correspondiente
	openFiles (infile, ionosphere);
	readData(infile,datos);
	//readData(infile,datos1);

	//Normalizamos los datos y los mezclamos
	Normalizar(datos); 
	random_shuffle(datos.begin(),datos.end());


	//5-fold Cross Validation 1NN
	//Inicializamos el vector de pesos a 1 para que la distancia ponderada coincida con la euclídea.
	for(int i=0; i<datos[0].first.size();i++){
		w.push_back(1.0);
	}
	cout<< "*************************************"<<endl;
	cout<< "ALGORITMO 1-NN" <<endl;
	cout<< "*************************************"<<endl;

	for(int i=1; i<6; i++){
		cout << "Iteracion: " << i << endl;
		//Dividimos en conjunto de entrenamiento (80%) y validacion (20%)
		Prepara5FoldCrossVal(datos,entrenamiento,validacion,i);
		cout << "Numero de elementos en entrenamiento: " << entrenamiento.size() << endl;
		cout << "Numero de elementos en validacion: " << validacion.size() << endl;
		//Obtenemos el valor de tasa_clas en entrenamiento
		tasa_clas=LeaveOneOut(entrenamiento,w);
		cout <<"\t Tasa_clas entrenamiento:" << tasa_clas <<endl;
		
		//Obtenemos el valor de tasa_red en entrenamiento
		tasa_red_=tasa_red(w);
		cout <<"\t Tasa_red entrenamiento:" << tasa_red_<<endl;

		//Obtenemos la función de evaluación en entrenamiento
		funcion_evaluacion=funcionEvaluacion(tasa_clas,tasa_red_);
		cout <<"\t Funcion objetivo entrenamiento:" << funcion_evaluacion<<endl;
		
		//Obtenemos tiempo de ejecución en entrenamiento
		cout <<"\t Tiempo de ejecución entrenamiento: " << 0.0 <<"ms"<<endl;

		cout <<endl;
		//Obtenemos el valor de tasa_clas en validacion
		tasa_clas=Evaluacion(entrenamiento,validacion,w);
		tasa_clas_promedio+=tasa_clas;
		cout <<"\t Tasa_clas validacion:" << tasa_clas <<endl;
		
		//Obtenemos el valor de tasa_red en validacion
		tasa_red_=tasa_red(w);
		tasa_red_promedio+=tasa_red_;
		cout <<"\t Tasa_red validacion:" << tasa_red_<<endl;

		//Obtenemos la función de evaluación en validacion
		funcion_evaluacion=funcionEvaluacion(tasa_clas,tasa_red_);
		funcion_evaluacion_promedio+=funcion_evaluacion;
		cout <<"\t Funcion objetivo validacion:" << funcion_evaluacion<<endl;
	}

	cout << endl;
	cout << endl;
	cout << "MEDIA 1-NN"<<endl;
	cout << "Tasa clasificacion promedio: " << tasa_clas_promedio/5 <<endl;
	cout << "Tasa reduccion promedio: " << tasa_red_promedio/5<<endl;
	cout << "Funcion Evaluacion promedio: "<< funcion_evaluacion_promedio/5 << endl;
	
	//5-Fold Cross Validation RELIEF
	tasa_clas_promedio=0.0;
	tasa_red_promedio=0.0;
	funcion_evaluacion_promedio=0.0;
	cout<< "*************************************"<<endl;
	cout<< "ALGORITMO RELIEF" <<endl;
	cout<< "*************************************"<<endl;
	for(int i=1; i<6; i++){
		cout << "Iteracion: " << i << endl;
		//Dividimos en conjunto de entrenamiento (80%) y validacion (20%)
		Prepara5FoldCrossVal(datos,entrenamiento,validacion,i);
		
		cout << "Numero de elementos en entrenamiento: " << entrenamiento.size() << endl;
		cout << "Numero de elementos en validacion: " << validacion.size() << endl;
		
		t0=clock();
		w=metodoRELIEF(entrenamiento);
		t1=clock();

		cout <<endl;

		//Obtenemos el valor de tasa_clas en entrenamiento
		tasa_clas=LeaveOneOut(entrenamiento,w);
		cout <<"\t Tasa_clas entrenamiento:" << tasa_clas <<endl;
		
		//Obtenemos el valor de tasa_red en entrenamiento
		tasa_red_=tasa_red(w);
		cout <<"\t Tasa_red entrenamiento:" << tasa_red_<<endl;

		//Obtenemos la función de evaluación en entrenamiento
		funcion_evaluacion=funcionEvaluacion(tasa_clas,tasa_red_);
		cout <<"\t Funcion objetivo entrenamiento:" << funcion_evaluacion<<endl;
		
		//Obtenemos tiempo de ejecución en entrenamiento
		tiempo=1000*(double(t1-t0)/CLOCKS_PER_SEC);
		cout <<"\t Tiempo de ejecución entrenamiento: " << tiempo <<"ms"<<endl;

		cout <<endl;
		//Obtenemos el valor de tasa_clas en validacion
		tasa_clas=Evaluacion(entrenamiento,validacion,w);
		tasa_clas_promedio+=tasa_clas;
		cout <<"\t Tasa_clas validacion:" << tasa_clas <<endl;
		
		//Obtenemos el valor de tasa_red en validacion
		tasa_red_=tasa_red(w);
		tasa_red_promedio+=tasa_red_;
		cout <<"\t Tasa_red validacion:" << tasa_red_<<endl;

		//Obtenemos la función de evaluación en validacion
		funcion_evaluacion=funcionEvaluacion(tasa_clas,tasa_red_);
		funcion_evaluacion_promedio+=funcion_evaluacion;
		cout <<"\t Funcion objetivo validacion:" << funcion_evaluacion<<endl;
	}

	cout << endl;
	cout << endl;
	cout << "MEDIA RELIEF"<<endl;
	cout << "Tasa clasificacion promedio: " << tasa_clas_promedio/5 <<endl;
	cout << "Tasa reduccion promedio: " << tasa_red_promedio/5<<endl;
	cout << "Funcion Evaluacion promedio: "<< funcion_evaluacion_promedio/5 << endl;
	

	//5-fold Cross Validation con BL.
	tasa_clas_promedio=0.0;
	tasa_red_promedio=0.0;
	funcion_evaluacion_promedio=0.0;
	cout<< "*************************************"<<endl;
	cout<< "ALGORITMO Busqueda Local" <<endl;
	cout<< "*************************************"<<endl;

	for (int i=1; i<6; i++){
		cout << "Iteracion: " << i << endl;
		Prepara5FoldCrossVal(datos,entrenamiento,validacion,i);
		w=inicializacionBL(datos[0].first.size(),i);

		//Calculamos tiempo que tarda el algoritmo
		t0=clock();
		BusquedaLocal(entrenamiento,w,i);
		t1=clock();

		//Obtenemos tiempo de ejecución en validacion
		tiempo=1000*(double(t1-t0)/CLOCKS_PER_SEC);
		cout <<"\t Tiempo de ejecución entrenamiento: " << tiempo <<"ms"<<endl;

		cout <<endl;
		//Obtenemos el valor de tasa_clas en validacion
		tasa_clas=Evaluacion(entrenamiento,validacion,w);
		tasa_clas_promedio+=tasa_clas;
		cout <<"\t Tasa_clas validacion:" << tasa_clas <<endl;
		
		//Obtenemos el valor de tasa_red en validacion
		tasa_red_=tasa_red(w);
		tasa_red_promedio+=tasa_red_;
		cout <<"\t Tasa_red validacion:" << tasa_red_<<endl;

		//Obtenemos la función de evaluación en validacion
		funcion_evaluacion=funcionEvaluacion(tasa_clas,tasa_red_);
		funcion_evaluacion_promedio+=funcion_evaluacion;
		cout <<"\t Funcion objetivo validacion:" << funcion_evaluacion<<endl;

		cout << "Solucion obtenida: "<<endl;
		for (int j=0; j<w.size(); j++){
			cout << w[j]<<", ";
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;
	cout << "MEDIA BUSQUEDA LOCAL"<<endl;
	cout << "Tasa clasificacion promedio: " << tasa_clas_promedio/5 <<endl;
	cout << "Tasa reduccion promedio: " << tasa_red_promedio/5<<endl;
	cout << "Funcion Evaluacion promedio: "<< funcion_evaluacion_promedio/5 << endl;

}