#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "../include/utilidades.h"
#include "../include/RELIEF.h"
#include "../include/BL.h"
#include "../include/AGG.h"
#include "../include/AGE.h"
#include "../include/AM.h"
#include "../include/BMB.h"
#include "../include/ILS.h"
#include "../include/ES.h"

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

void ImprimeSolucion(vector<double> const& w){
		cout << "Solucion obtenida: "<<endl;
		for (int j=0; j<w.size(); j++){
			cout << w[j]<<", ";
		}
		cout << endl;
}

int main(int argc, char *argv[])
{	

	//Comprobación de si se llama con parámetros
	if (argc==1)
   {
       cout << "Debes indicar la base de datos...\n";
       return 1;
   }
	//Declaración de variables
	ifstream infile; //Variable de tipo ifstream para leer de fichero
	//La estructura de datos que usaremos será un vector de pares vector-etiqueta
	vector<pair<vector<double>,string>> datos;
	string argumento= argv[1]; //Capturamos el argumento con el que se invoca
	//Variables para separar entre entrenamiento y test en Cross Validation
	vector<pair<vector<double>,string>> entrenamiento;
	vector<pair<vector<double>,string>> validacion;
	//Vector de pesos
	vector<double> w;
	vector<double> w_solucion;
	//Variables para recoger estadísticas
	double tasa_clas=0;
	double tasa_red_=0;
	double funcion_evaluacion=0;
	double tasa_clas_promedio=0.0;
	double tasa_red_promedio=0.0;
	double funcion_evaluacion_promedio=0.0;
	unsigned t0,t1;
	double tiempo=0.0;
	double tiempo_promedio=0.0;

	//Leemos los datos del fichero correspondiente
	cout << argv[1] << endl;
	if(argumento=="parkinsons"){
		openFiles (infile, parkinsons);
		readData(infile,datos);
	} else if (argumento=="heart"){
		openFiles (infile, spectf_heart);
		readData(infile,datos);	
	} else if (argumento=="ionosphere"){
		openFiles (infile, ionosphere);
		readData(infile,datos);			
	}else {
		cout<< "Los argumentos son incorrectos, los argumentos validos son: \n 1.parkinsons \n 2.heart \n 3.ionosphere\n";
		return 1;
	}
	//Normalizamos los datos y los mezclamos
	Normalizar(datos); 
	random_shuffle(datos.begin(),datos.end());

	//Vector con los nombres de los algoritmos, usado solo para la salida por pantalla: 
	vector<string> algoritmos;
	algoritmos.push_back("1-NN");
	algoritmos.push_back("RELIEF");
	algoritmos.push_back("Busqueda Local");
	algoritmos.push_back("AGG-BLX");
	algoritmos.push_back("AGG-ARITMETICO");
	algoritmos.push_back("AGE-BLX");
	algoritmos.push_back("AGE-ARITMETICO");
	algoritmos.push_back("AM(10,1.0)");
	algoritmos.push_back("AM(10,0.1)");
	algoritmos.push_back("AM(10,0.1Mej)");
	algoritmos.push_back("Enfriamiento Simulado");
	algoritmos.push_back("BMB");
	algoritmos.push_back("ILS con Búsqueda Local");
	algoritmos.push_back("ILS con Enfriamiento Simulado");




	mt19937 gen(1);
	/*
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
		t0=clock();
		tasa_clas=LeaveOneOut(entrenamiento,w);
		t1=clock();

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
		tiempo_promedio+=tiempo;

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
	cout << "\tTasa clasificacion promedio: " << tasa_clas_promedio/5 <<endl;
	cout << "\tTasa reduccion promedio: " << tasa_red_promedio/5<<endl;
	cout << "\tFuncion Evaluacion promedio: "<< funcion_evaluacion_promedio/5 << endl;
	*/

	for (int k=12; k<algoritmos.size(); k++){
		cout<< "*************************************"<<endl;
		cout<< "ALGORITMO " << algoritmos[k] <<endl;
		cout<< "*************************************"<<endl;

		//Inicializamos el vector solucion.
		for(int i=0; i<datos[0].first.size();i++){
			w_solucion.push_back(0.0);
		}

		for (int i=1; i<6; i++){
			cout << "\nIteracion: " << i << endl;
			Prepara5FoldCrossVal(datos,entrenamiento,validacion,i);
			//Calculamos tiempo que tarda el algoritmo
			cout << "K=" << k <<endl;
			if(k==1){
				t0=clock();
				w=metodoRELIEF(entrenamiento);
				t1=clock();
			}
			else if(k==2){
				w=inicializacionBL(datos[0].first.size(),gen);
				t0=clock();
				BusquedaLocal(entrenamiento,w,gen,w.size(),15000);
				t1=clock();
			}
			else if(k==3){
				t0=clock();
				AlgoritmoGeneticoGeneracional(datos,w,30,1,gen);
				t1=clock();
			}
			else if(k==4){
				t0=clock();
				AlgoritmoGeneticoGeneracional(datos,w,30,2,gen);
				t1=clock();
			}
			else if(k==5){
				t0=clock();
				AlgoritmoGeneticoEstacionario(datos,w,30,1,gen);
				t1=clock();
			}
			else if(k==6){
				t0=clock();
				AlgoritmoGeneticoEstacionario(datos,w,30,2,gen);
				t1=clock();
			}
			else if(k==7){
				t0=clock();
				AlgoritmoMemetico(datos,w,10,i,1,1.0,false,gen);
				t1=clock();
			}
			else if(k==8){
				t0=clock();
				AlgoritmoMemetico(datos,w,10,i,1,0.1,false,gen);
				t1=clock();
			}
			else if(k==9){
				t0=clock();
				AlgoritmoMemetico(datos,w,10,i,1,0.1,true,gen);
				t1=clock();
			}else if(k==10){
				t0=clock();
				EnfriamientoSimulado(entrenamiento,w,gen,0.001,0.3,0.3);
				t1=clock();
			}else if(k==11){
				t0=clock();
				BusquedaMultiarranqueBasica(entrenamiento,w,gen,w.size(),15000,15);
				t1=clock();
			}else if(k==12){
				t0=clock();
				MetodoILS(entrenamiento,validacion,w,gen,w.size(),15000,15);
				t1=clock();
			}else if(k==13){
				t0=clock();
				MetodoILS_ES(entrenamiento,validacion,w,gen,w.size(),15000,15);
				t1=clock();
			}

			//Obtenemos tiempo de ejecución en validacion
			tiempo=1000*(double(t1-t0)/CLOCKS_PER_SEC);
			tiempo_promedio+=tiempo;
			cout <<"\t Tiempo de ejecución entrenamiento: " << tiempo <<"ms"<<endl;

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
			
			cout << "FORMATO PARA COPIAR A TABLA: " << endl;
			cout << "| " << tasa_clas << "| " << tasa_red_ << "| " << funcion_evaluacion << "| " << tiempo << "| " << endl;
			//Acumulamos en el vector solucion
			w_solucion=w_solucion+w;
			ImprimeSolucion(w);
		}

		//Dividimos cada componente del vector entre 5 para obtener el vector promedio
		for(int i=0; i<w_solucion.size();i++){
			w_solucion[i]=w_solucion[i]/5;
		}
		cout << endl;
		cout << endl;
		cout << "MEDIA " << algoritmos[k] <<endl;
		cout << "\tTasa clasificacion promedio: " << tasa_clas_promedio/5 <<endl;
		cout << "\tTasa reduccion promedio: " << tasa_red_promedio/5<<endl;
		cout << "\tFuncion Evaluacion promedio: "<< funcion_evaluacion_promedio/5 << endl;
		cout << "\tTiempo promedio: " << tiempo_promedio/5 <<endl;
		cout << "FORMATO PARA COPIAR A TABLA: " << endl;
		cout << "| " << tasa_clas_promedio/5 << "| " << tasa_red_promedio/5 << "| " << funcion_evaluacion_promedio/5 << "| " << tiempo_promedio/5 << "| " << endl;
		ImprimeSolucion(w_solucion);
		tasa_clas_promedio=0.0;
		tasa_red_promedio=0.0;
		funcion_evaluacion_promedio=0.0;
		tiempo_promedio=0.0;
		w_solucion.clear();
	}
	
}