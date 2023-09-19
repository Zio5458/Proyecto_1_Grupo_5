#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1
#include <experimental/filesystem>
#include <iomanip>
#include "Alumno.h"
using namespace std;
namespace fs = std::experimental::filesystem;

bool compararAlumno(Alumno* a, Alumno* b) { return a->getAudio() < b->getAudio(); }

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



int main() {

	vector<Alumno*> alumnos;
	string semana;
	string base = "Contenido del Curso";
	string fecha = "2021-07-20";
	int vueltas = 1;
	for (int i = 1; i <= 5; i++) {
		semana = "Semana 0" + to_string(i);
		bool empezo = false;
		switch (i) {
		case 1:
			fecha = "2021-07-20";
			break;
		case 2:
			fecha = "2021-07-26";
			break;
		case 3:
			fecha = "2021-08-02";
			break;
		case 4:
			fecha = "2021-08-10";
			break;
		case 5:
			fecha = "2021-08-16";
			break;

		}
		vueltas = 1;
		string directory = base + "/" + semana + "/" + fecha + ".txt";
		fstream* file = new fstream(directory, ios::in);

		std::experimental::filesystem::path fs = directory;
		int count = 0;
		std::experimental::filesystem::path p1 = fs.parent_path();
		for (auto& p : std::experimental::filesystem::directory_iterator(p1))
		{
			++count;
		}
		while (vueltas <= count) {
			vueltas++;
			directory = base + "/" + semana + "/" + fecha + ".txt";
			file = new fstream(directory, ios::in);
			if (!file) {
				if (empezo) break;
			}
			else {
				empezo = true;
				string linea;
				string nom = "";
				bool audio = true;
				cout << "*REVISANDO EL ARCHIVO: ";
				cout << experimental::filesystem::absolute(fs) << "\n";
				cout << endl << "	";
				file->seekg(0);
				//cout << "impresion\n";
				string lineaVacia = "";
				string fechaComparar = fecha + ":";
				string nombre = ""; bool verificar = true; //si la variable verificar es true, se crea un alumno, a lo contrario, solo se actualiza;
				size_t find; //usada para el String::find()

				while (getline(*file, linea)) {
					verificar = true;
					if (linea == fechaComparar || linea.size() == 0) { cout << "I"; }
					else {
						//este for es para actualizar o crear un alumno en el vector
						for (int j = 0; j < linea.size(); j++) {
							if (linea.at(j) == ' ') {
								break;
							}
							else {
								nombre += linea.at(j);
								if (nombre.size() == linea.size() || linea.at(j + 1) == ' ') {
									for (Alumno* alu : alumnos) {
										if (alu->getNombre() == nombre) {
											verificar = false;

											find = linea.find("NO_AUDIO");
											if (find != string::npos) {
												alu->addAudio(false);
											}
											else {
												alu->addAudio(true);
											}
											cout << "[" << nombre << "][A]FU, ";
											nombre = "";
											break;
										}
									}
								}

							}
						}
						if (verificar) { //agrega el estudiante si no esta en el vector
							if (nombre == "EXAMEN" || nombre == "ASISTIERON TODOS" || nombre == "EXAMENASISTIERON") {
								cout << "I";
							}
							else {
								cout << "[" << nombre << "][A] NC, ";

								Alumno* a = new Alumno(nombre);
								nombre = "";
								find = linea.find("NO_AUDIO");
								if (find == string::npos) { a->addAudio(true); }
								else { a->addAudio(true); }

								alumnos.push_back(a);
							}

						}

					}

				}
				cout << endl << endl;
				cout << lineaVacia;
				fecha = ajustarFecha(fecha);
				file->close();
				delete file;
			}
		}
	}//fin for
	cout << "*LISTADO:" << endl;
	cout << "=========" << endl;
	cout << setw(16) << "ALUMNO" << setw(8) << "AUDIO " << "NO-AUDIO " << "ASISTENCIAS " << "PORCENTAJE" << endl;
	cout << setw(16) << "------" << setw(8) << "----- " << "-------- " << "----------- " << "----------" << endl;
	for (int i = 0; i < alumnos.size(); i++) {
		for (int j = 0; j < alumnos.size() - 1; j++) {
			if (compararAlumno(alumnos[j], alumnos[j + 1])) {
				Alumno* temp = alumnos[j];
				alumnos[j] = alumnos[j + 1];
				alumnos[j + 1] = temp;
			}
		}
	}//ordenamiento del vector en base a la variable audio
	for (int i = 0; i < alumnos.size(); i++) {
		cout << fixed << setprecision(2);
		double porcentaje = (static_cast<double>(alumnos[i]->getAudio()) / alumnos[i]->getAsistencias()) * 100;
		cout << setw(16) << alumnos[i]->getNombre() << setw(8) << alumnos[i]->getAudio() << setw(8) << alumnos[i]->getNoAudio() << setw(12) << alumnos[i]->getAsistencias() << setw(10) << porcentaje << "%" << endl;
	}
}