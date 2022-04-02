#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include "../include/funciones.h"
#include <ctime> 

using namespace std;

ifstream infile;
ofstream outfile;
string ionosphere="Instancias_APC/ionosphere.arff";
string parkinsons="Instancias_APC/parkinsons.arff";
string spectf_heart="Instancias_APC/spectf-heart.arff";


void openFiles (ifstream& infile, ofstream& output, string filename){
	outfile.open("OutPut.txt"); //TODO--Revisar si esto lo necesito 
	infile.open(filename);
		if (!infile)
		{
			cout << "Cannot open the input file. Program terminates!"<< endl;
		}
}

void readDataFromIonosphere(ifstream &infile, vector<pair<vector<double>,string>> &datos2){
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
		datos2.push_back(make_pair(row,etiqueta));
		row.clear();
	}

	cout << "Data tiene las dimensiones: " << datos2.size() << endl;
}

void readData(ifstream &infile, vector<pair<vector<double>,int>> &datos1){
	string text_line;
	vector <double> row;
	int etiqueta;
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
			//cout<<"cadena: " << substr << endl;
			row.push_back(stof(substr));			
		}
		etiqueta=row.back();
		row.pop_back();
		datos1.push_back(make_pair(row,etiqueta));
		row.clear();
	}
	cout << "Data tiene las dimensiones: " << datos1.size()<< endl;
}


int main(int argc, char *argv[])
{
	ifstream infile;
	ofstream outfile;
	vector<pair<vector<double>,int>> datos1;
	vector<pair<vector<double>,string>> datos2;

	vector<double> ejemplo;
	openFiles (infile, outfile, ionosphere);
	readDataFromIonosphere(infile,datos2);
	
	//readData(infile,datos1);

	
	//5-Fold Cross Validation RELIEF
	random_shuffle(datos2.begin(),datos2.end());
	vector<pair<vector<double>,string>> entrenamiento;
	vector<pair<vector<double>,string>> validacion;
	vector<double> w;
	double tasa_clas=0;
	double tasa_red_=0;
	double funcion_evaluacion=0;
	unsigned t0,t1;
	double tiempo=0.0;

	for(int i=1; i<6; i++){
		cout << "Iteracion: " << i << endl;
		Prepara5FoldCrossVal(datos2,entrenamiento,validacion,i);
		
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
		tasa_clas=LeaveOneOut(validacion,w);
		cout <<"\t Tasa_clas validacion:" << tasa_clas <<endl;
		
		//Obtenemos el valor de tasa_red en validacion
		tasa_red_=tasa_red(w);
		cout <<"\t Tasa_red validacion:" << tasa_red_<<endl;

		//Obtenemos la función de evaluación en validacion
		funcion_evaluacion=funcionEvaluacion(tasa_clas,tasa_red_);
		cout <<"\t Funcion objetivo validacion:" << funcion_evaluacion<<endl;
	}


	//5-fold Cross Validation con BL.
}