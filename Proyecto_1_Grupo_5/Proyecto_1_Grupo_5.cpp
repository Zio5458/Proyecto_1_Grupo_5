#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1
#include <experimental/filesystem>

#include "Alumno.h"

using namespace std;

namespace fs = std::experimental::filesystem;

bool encontrarAlumno(vector<Alumno*>& a, string nombre) {
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
	string base = "Contenido del Curso";
	string fecha = "2021-07-20";


	for (int i = 1; i <= 5; i++) {
		semana = "Semana 0" + to_string(i);
		bool empezo = false;
		while (i == 1) {
			i++;
			string directory = base + "/" + semana + "/" + fecha + ".txt";
			fstream* file = new fstream(directory, ios::in);

			if (file->is_open()) cout << "Samuel sos un caregei\n";
			if (!file) {
				if (empezo) break;
			}
			else {
				empezo = true;
				string linea;
				string nom = "";
				bool audio = true;
				cout << "*REVISANDO EL ARCHIVO:" << endl;
				std::experimental::filesystem::path fs = directory;
				cout << std::experimental::filesystem::absolute(fs) << "\n";

				file->seekg(0);

				cout << "impresion\n";

				while (getline(*file, linea)) {


					cout << linea << "\n";

					/*if (((int)linea.at(0) >= 48 && (int)linea.at(0) <= 57) || linea.at(0) == ' ') {
						cout << "I";
					}
					for (int i = 0; i < linea.length(); i++) {
						if (linea.at(i) != ' ') {
							nom += linea.at(i);
						}
						else {
							cout << "[" + nom + "]";
							for (int j = i; j < linea.length(); j++) {
								if (linea.at(i) != '-') {
									audio = false;
									break;
								}
								audio = true;
							}
							if (!encontrarAlumno(alumnos, nom)) {
								Alumno* a = new Alumno(nom);
								a->addAudio(audio);
								alumnos.push_back(a);
							}
							break;
						}
					}*/
				}
			}
			ajustarFecha(fecha);
			file->close();
			delete file;
		}
	}
}