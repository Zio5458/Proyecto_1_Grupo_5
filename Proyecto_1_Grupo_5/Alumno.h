#pragma once
#include <string>
using namespace std;
class Alumno
{
private:
	string nombre;
	int audio;
	int no_audio;
	int asistencias;
	double porcentaje;
public:
	Alumno(string);
	string getNombre();
	int getAudio();
	int getNoAudio();
	int getAsistencias();
	double getPorcentaje();
	void addAudio(bool);
};