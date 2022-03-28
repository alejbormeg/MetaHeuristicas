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

void readDataFromIonosphere(ifstream &infile, vector<vector <double>> &data ,vector<string> & classes ){
	string text_line;
	vector <double> row;

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
				classes.push_back(substr);
			} else{
				row.push_back(stof(substr));
			}		
			
		}
		data.push_back(row);
		row.clear();
	}

	cout << "Data tiene las dimensiones: " << data.size() << endl;
	cout << "Classes tiene estas dimensiones: " << classes.size() << endl;
}

void preparaEtiquetas(vector<vector <double>> &data,vector <int> & classes){
	int tam_fila=data[0].size();
	for (int i=0; i<data.size(); i++){
		classes.push_back(data[i][tam_fila-1]);
		data[i].pop_back();
	}
}

void readData(ifstream &infile, vector<vector <double>> &data, vector <int> & classes){
	string text_line;
	vector <double> row;

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
		data.push_back(row);
		row.clear();
	}

	preparaEtiquetas(data, classes);

	cout << "Data tiene las dimensiones: " << data.size()<< endl;
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
T Clasificador1NN( vector< vector <double>> &datos, vector<T> & etiquetas, vector<double> nuevo_ejemplo) {
	T cmin=etiquetas[0];
	double dmin=distanciaEuclidea(datos[0],nuevo_ejemplo);
	double distancia=0;

	for (int i=1; i<datos.size(); i++){
		distancia=distanciaEuclidea(datos[i],nuevo_ejemplo);
		if(distancia < dmin){
			dmin=distancia;
			cmin=etiquetas[i];
			cout << "Nueva distancia: " << dmin << " con el elemento " << cmin << endl;
		}
	}

	return cmin;
}

int main(int argc, char *argv[])
{
	ifstream infile;
	ofstream outfile;
	vector< vector <double>> data;
	vector<string> classes;
	vector<int> clases;
	vector<double> ejemplo;
	openFiles (infile, outfile, spectf_heart);
	//readDataFromIonosphere(infile,data,classes);
	readData(infile,data,clases);

	for (int i=0; i<data.size(); i++){
		cout << "dim fila " << data[i].size() << endl;
		cout << "i: " << i << endl;
	}

	for (int i=0; i<45; i++){
		ejemplo.push_back(1.0);
	}

	int a= Clasificador1NN(data,clases,ejemplo);
	cout << "Dimenison etiquetas: " << clases.size() << endl;
	cout << "Etiqueta asignada: " << a << endl;

}