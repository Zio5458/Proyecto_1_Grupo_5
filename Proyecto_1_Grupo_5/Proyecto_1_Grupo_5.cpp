#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include "Alumno.h"
using namespace std;

bool encontrarAlumno(vector<Alumno*> &a, string nombre) {
	for (int i = 0; i < a.size(); i++) 
		if (a[i]->getNombre() == nombre) return true;
	return false;
}

string ajustarFecha(string s) {
	string a, m, d;
	int k;
	for (int i = 0; i < s.length(); i++) {
		if (s.at(i) != '-') {
			a += s.at(i);
		}
		else {
			k = i + 1;
			break;
		}
	}//a
	for (int i = k; i < s.length(); i++) {
		if (s.at(i) != '-') {
			m += s.at(i);
		}
		else {
			k = i + 1;
			break;
		}
	}//m
	int mes = stoi(m);
	for (int i = k; i < s.length(); i++) {
		if (s.at(i) != ' ')  d += s.at(i);
		else break;
	}
	int dia = stoi(d);
	dia++;
	if (dia > 31) {
		mes++;
		d = "01";
	}
	else {
		if (dia < 10)
			d = "0" + to_string(dia);
		else
			d = to_string(dia);
	}
	string temp = a + "-" + m + "-" + d;
	return temp;
}

int main()
{
	vector<Alumno*> alumnos;
	string semana;
	string fecha = "2022-07-20";
	for (int i = 1; i <= 5; i++) {
		semana = "Semana 0" + to_string(i);
		bool empezo = false;
		while (true) {
			string directory = semana + "/" + fecha + ".txt";
			fstream file;
			file.open(directory, ios::in);
			if (file.eof()) {
				ajustarFecha(fecha);
				if (empezo) break;
			}
			else {
				empezo = true;
				string linea;

				cout << "*REVISANDO EL ARCHIVO:" << endl;
				while (getline(file, linea)) {
					if (((int)linea.at(0) >= 48 && (int)linea.at(0) <= 57) || linea.at(0) == ' ') {
						cout << "I";
					}
				}
			}
			file.close();
		}
	}
}