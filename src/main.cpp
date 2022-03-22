#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>

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

void readData(ifstream &infile, vector<vector <double>> &data){
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

	cout << "Data tiene las dimensiones: " << data.size()<< endl;
}

int main(int argc, char *argv[])
{
	ifstream infile;
	ofstream outfile;
	vector< vector <double>> data;
	vector<string> classes;

	openFiles (infile, outfile, ionosphere);
	readDataFromIonosphere(infile,data,classes);
	//readData(infile,data);

	for (int i=0; i<data.size(); i++){
		cout << "dim fila " << data[i].size() << endl;
		cout << "i: " << i << endl;
	}
}