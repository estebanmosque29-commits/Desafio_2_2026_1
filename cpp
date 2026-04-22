EstadisticaJugador.cpp

#include "EstadisticaJugador.h"

EstadisticaJugador::EstadisticaJugador() {
    partidos = 0;
    goles = 0;
}

EstadisticaJugador::EstadisticaJugador(const EstadisticaJugador& otra) {
    partidos = otra.partidos;
    goles = otra.goles;
}

void EstadisticaJugador::setGoles(int g) {
    goles = g;
}

int EstadisticaJugador::getGoles() {
    return goles;
}

EstadisticaJugador EstadisticaJugador::operator+(const EstadisticaJugador& otra) {
    EstadisticaJugador temp;
    temp.goles = this->goles + otra.goles;
    temp.partidos = this->partidos + otra.partidos;
    return temp;
}


Jugador.cpp

#include "Jugador.h"
#include <cstring>

Jugador::Jugador() {
    nombre = NULL;
    numero = 0;
    estadisticas = new EstadisticaJugador();
}

Jugador::Jugador(const char* nom, int num) {
    nombre = new char[strlen(nom) + 1];
    strcpy(nombre, nom);
    numero = num;
    estadisticas = new EstadisticaJugador();
}

Jugador::Jugador(const Jugador& otro) {
    nombre = new char[strlen(otro.nombre) + 1];
    strcpy(nombre, otro.nombre);
    numero = otro.numero;
    estadisticas = new EstadisticaJugador(*otro.estadisticas);
}

Jugador::~Jugador() {
    delete[] nombre;
    delete estadisticas;
}

void Jugador::setNombre(const char* nom) {
    delete[] nombre;
    nombre = new char[strlen(nom) + 1];
    strcpy(nombre, nom);
}

char* Jugador::getNombre() {
    return nombre;
}

bool Jugador::operator==(const Jugador& otro) {
    return strcmp(this->nombre, otro.nombre) == 0;
}
