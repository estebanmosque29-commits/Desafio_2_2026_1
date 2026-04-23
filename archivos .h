EstadisticaJugador.h

#ifndef ESTADISTICAJUGADOR_H
#define ESTADISTICAJUGADOR_H

class EstadisticaJugador {
private:
    int partidos;
    int goles;

public:
    EstadisticaJugador();
    EstadisticaJugador(const EstadisticaJugador& otra);

    void setGoles(int g);
    int getGoles();

    EstadisticaJugador operator+(const EstadisticaJugador& otra);
};

#endif


Jugador.h

#ifndef JUGADOR_H
#define JUGADOR_H

#include "EstadisticaJugador.h"

class Jugador {
private:
    char* nombre;
    int numero;
    EstadisticaJugador* estadisticas;

public:
    Jugador();
    Jugador(const char* nom, int num);
    Jugador(const Jugador& otro);
    ~Jugador();

    void setNombre(const char* nom);
    char* getNombre();

    bool operator==(const Jugador& otro);
};

#endif


DirectorTecnico.h


#ifndef DIRECTORTECNICO_H
#define DIRECTORTECNICO_H

class DirectorTecnico {
private:
    char* nombre;

public:
    DirectorTecnico();
    DirectorTecnico(const char* nom);
    DirectorTecnico(const DirectorTecnico& otro);
    ~DirectorTecnico();
};

#endif
