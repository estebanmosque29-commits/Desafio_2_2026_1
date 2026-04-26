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


main.cpp

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "Equipo.h"
#include "Lista.h"
#include "partido.h"

long contadorIteraciones = 0;

void ordenarGrupo(Equipo* grupo[4]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i; j++) {
            grupo[j]->diferenciaGoles = grupo[j]->golesFavor - grupo[j]->golesContra;
            grupo[j+1]->diferenciaGoles = grupo[j+1]->golesFavor - grupo[j+1]->golesContra;
            if (grupo[j]->puntos < grupo[j+1]->puntos || (grupo[j]->puntos == grupo[j+1]->puntos && grupo[j]->diferenciaGoles < grupo[j+1]->diferenciaGoles)) {
                Equipo* temp = grupo[j];
                grupo[j] = grupo[j+1];
                grupo[j+1] = temp;
            }
        }
    }
}

void cargarCSV(Lista<Equipo>& lista) {
    std::ifstream archivo("selecciones clasificadas mundial.csv");
    if (!archivo.is_open()) { std::cout << "Error CSV." << std::endl; return; }
    char linea[1024]; archivo.getline(linea, 1024);
    while (archivo.getline(linea, 1024)) {
        Equipo e;
        std::sscanf(linea, "%[^,],%d,%lf,%lf,%s", e.nombre, &e.ranking, &e.gf_historicos, &e.gc_historicos, e.confederacion);
        e.inicializarPlantilla();
        e.repartirGolesHistoricos(contadorIteraciones);
        lista.agregar(e);
    }
    archivo.close();
    std::cout << "Equipos cargados: " << lista.size() << std::endl;
}

int main() {
    Lista<Equipo> equipos(&contadorIteraciones);
    char entrada[256]; int opcion = -1;

    do {
        std::cout << "\n--- UdeA WORLD CUP 2026 ---\n1. Cargar Datos\n2. Simular Fase de Grupos y Tablas\n3. Metricas\n0. Salir\nSeleccione: ";
        std::cin.getline(entrada, 256); opcion = std::atoi(entrada);

        if (opcion == 1) cargarCSV(equipos);
        else if (opcion == 2) {
            if (equipos.size() < 48) { std::cout << "Cargue 48 equipos." << std::endl; continue; }
            for (int g = 0; g < 12; g++) {
                Equipo* grupo[4];
                for(int i=0; i<4; i++) { grupo[i] = &equipos.obtener(g*4+i); grupo[i]->resetearEstadisticasTorneo(); }

                for(int i=0; i<4; i++)
                    for(int j=i+1; j<4; j++) { Partido p; p.e1 = grupo[i]; p.e2 = grupo[j]; p.simular(contadorIteraciones, false); }

                ordenarGrupo(grupo);
                std::cout << "\nGRUPO " << (char)('A'+g) << " | PTS | DG |" << std::endl;
                for(int i=0; i<4; i++) std::cout << i+1 << ". " << grupo[i]->nombre << "\t" << grupo[i]->puntos << "\t" << grupo[i]->diferenciaGoles << std::endl;
            }
        }
        else if (opcion == 3) {
            std::cout << "Iteraciones: " << contadorIteraciones << std::endl;
            // Memoria: Equipos + Jugadores (26 por equipo)
            long mem = (sizeof(Equipo) + (sizeof(Jugador) * 26)) * equipos.size();
            std::cout << "Memoria: " << mem << " bytes" << std::endl;
        }
    } while (opcion != 0);
    return 0;
}
