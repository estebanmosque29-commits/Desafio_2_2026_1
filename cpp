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


Jugador.cpp

#include "Jugador.h"
#include <cstring>

Jugador::Jugador() {
    std::strcpy(nombre, "");
    std::strcpy(apellido, "");
    numero = 0;
    goles = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    faltas = 0;
    minutosJugados = 0;
}


partido.cpp

#include "partido.h"
#include <cmath>

Partido::Partido() : e1(nullptr), e2(nullptr), golesE1(0), golesE2(0) {}

void Partido::simular(long& iteraciones, bool esEliminacion) {
    if (!e1 || !e2) return;

    double mu = 1.35, alpha = 0.6, beta = 0.4;
    double lambda1 = mu * std::pow((e1->gf_historicos / mu), alpha) * std::pow((e2->gc_historicos / mu), beta);
    double lambda2 = mu * std::pow((e2->gf_historicos / mu), alpha) * std::pow((e1->gc_historicos / mu), beta);

    golesE1 = std::round(lambda1);
    golesE2 = std::round(lambda2);

    if (esEliminacion && golesE1 == golesE2) {
        if (e1->ranking < e2->ranking) golesE1++; else golesE2++;
    }

    // Actualizar Tablas de Posiciones
    e1->golesFavor += golesE1; e1->golesContra += golesE2;
    e2->golesFavor += golesE2; e2->golesContra += golesE1;

    if (golesE1 > golesE2) e1->puntos += 3;
    else if (golesE2 > golesE1) e2->puntos += 3;
    else { e1->puntos += 1; e2->puntos += 1; }

    // RF I: Actualizar históricos tras el partido
    e1->gf_historicos += golesE1; e1->gc_historicos += golesE2;
    e2->gf_historicos += golesE2; e2->gc_historicos += golesE1;

    iteraciones++;
}
