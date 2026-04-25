Equipo.h

#ifndef EQUIPO_H
#define EQUIPO_H
#include "Jugador.h"

class Equipo {
public:
    char nombre[50];
    char confederacion[15];
    int ranking;
    double gf_historicos;
    double gc_historicos;
    Jugador plantilla[26];

    // Estadísticas para la Fase de Grupos (RF III)
    int puntos;
    int golesFavor;
    int golesContra;
    int diferenciaGoles;

    Equipo();
    void inicializarPlantilla();
    void repartirGolesHistoricos(long& iteraciones);
    void resetearEstadisticasTorneo();
};

#endif
