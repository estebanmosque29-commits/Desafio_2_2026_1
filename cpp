Equipo.cpp

#include "Equipo.h"
#include <cstring>
#include <cstdio>

Equipo::Equipo() {
    std::strcpy(nombre, "Sin Nombre");
    std::strcpy(confederacion, "N/A");
    ranking = 0;
    gf_historicos = 0.0;
    gc_historicos = 0.0;
    resetearEstadisticasTorneo();
}

void Equipo::resetearEstadisticasTorneo() {
    puntos = 0;
    golesFavor = 0;
    golesContra = 0;
    diferenciaGoles = 0;
}

void Equipo::inicializarPlantilla() {
    for (int i = 0; i < 26; i++) {
        plantilla[i].numero = i + 1;
        std::sprintf(plantilla[i].nombre, "Nombre%d", i + 1);
        std::sprintf(plantilla[i].apellido, "Apellido%d", i + 1);
        plantilla[i].goles = 0;
        plantilla[i].tarjetasAmarillas = 0;
        plantilla[i].tarjetasRojas = 0;
        plantilla[i].faltas = 0;
    }
}

void Equipo::repartirGolesHistoricos(long& iteraciones) {
    int totales = (int)gf_historicos;
    for (int i = 0; i < totales; i++) {
        plantilla[i % 26].goles++;
        iteraciones++;
    }
}
