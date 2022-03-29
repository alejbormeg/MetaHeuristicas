#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <cmath>

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

double distanciaEuclidea(vector<double> &e1, vector<double> &e2){
	double distancia;
	double suma=0; 
	double aux=0;

	for(int i=0; i<e1.size(); i++){
		aux=e1[i]-e2[i];
		suma+=aux*aux;
	}

	return sqrt(suma);
}

template <typename T>
T Clasificador1NN( vector<pair<vector<double>,T>> &datos, vector<double> nuevo_ejemplo) {
	T cmin=datos[0].second;
	double dmin=distanciaEuclidea(datos[0].first,nuevo_ejemplo);
	double distancia=0;

	for (int i=1; i<datos.size(); i++){
		distancia=distanciaEuclidea(datos[i].first,nuevo_ejemplo);
		if(distancia < dmin){
			dmin=distancia;
			cmin=datos[i].second;
			cout << "Nueva distancia: " << dmin << " con el elemento " << cmin << endl;
		}
	}

	return cmin;
}

double tasa_clas (int num_correctos, int num_elementos){
	return 100*(num_correctos/num_elementos);
}

double tasa_red (int num_valores, int num_caracteristicas){
	return 100*(num_valores/num_caracteristicas);
}

double funcionEvaluacion(int num_correctos, int num_elementos, vector<double>&w){
	int num_valores=0;

	for(int i=0; i<w.size();i++){
		if(w[i]<0.1)
			num_valores++;
	}

	return 0.5*tasa_clas(num_correctos,num_elementos)+0.5*tasa_red(num_valores,w.size());
}

template <typename T>
vector<T> preparaDatos(vector<pair<vector<double>,T>>a, int j){
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
	int num_elementos=entrenamiento.size()*entrenamiento[0].first.size();
	int num_correctos=0;
	T etiqueta_predicha;
	vector<pair<vector<double>,T>> one_out;

	for (int i=0; i<entrenamiento.size(); i++){
		one_out=preparaDatos(entrenamiento,i);
		etiqueta_predicha=Clasificador1NN(one_out,entrenamiento[i].first);
		if(etiqueta_predicha==entrenamiento[i].second)
			num_correctos++;
	}

	return num_correctos/num_elementos;
}

int main(int argc, char *argv[])
{
	ifstream infile;
	ofstream outfile;
	vector<pair<vector<double>,int>> datos1;
	vector<pair<vector<double>,string>> datos2;

	vector<double> ejemplo;
	openFiles (infile, outfile, spectf_heart);
	//readDataFromIonosphere(infile,datos2);
	readData(infile,datos1);

	/*
	for (int i=0; i<data.size(); i++){
		cout << "dim fila " << data[i].size() << endl;
		cout << "i: " << i << endl;
	}
	*/

	for (int i=0; i<45; i++){
		ejemplo.push_back(1.0);
	}

	
	int a= Clasificador1NN(datos1,ejemplo);
	cout << "Etiqueta asignada: " << a << endl;
	

	/*
	string clase= "g";
	double num_unos=0;
	double num_doses=0;

	for (int i=0; i<datos2.size();i++){

		cout << datos2[i].second << endl;
		
		if (datos2[i].second==clase)
			num_unos++;
		else 
			num_doses++;
		
	}
	cout <<"Porcentaje de unos: " << num_unos/datos2.size() << endl; 
	cout << "Porcentaje de doses: "<< num_doses/datos2.size() << endl;
	*/
}