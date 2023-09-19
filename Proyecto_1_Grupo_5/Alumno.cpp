#include "Alumno.h"
#include <iostream>
Alumno::Alumno(string nombre) {
	this->nombre = nombre;
	this->audio = 0;
	this->no_audio = 0;
	this->asistencias = 0;
}
string Alumno::getNombre() {
	return this->nombre;
}
int Alumno::getAudio() {
	return this->audio;
}
int Alumno::getNoAudio() {
	return this->no_audio;
}
int Alumno::getAsistencias() {
	return this->asistencias;
}
double Alumno::getPorcentaje() {
	return this->porcentaje;
}
void Alumno::addAudio(bool a) {
	if (a) {
		audio++;
	}
	else {
		no_audio++;
	}
	asistencias++;
}