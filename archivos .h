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


Jugador.h

#ifndef JUGADOR_H
#define JUGADOR_H

class Jugador {
public:
    char nombre[50];
    char apellido[50];
    int numero;
    int goles;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;
    int minutosJugados;

    Jugador();
};

#endif


Lista.h

#ifndef LISTA_H
#define LISTA_H

template <typename T>
class Lista {
private:
    T* elementos;
    int capacidad;
    int cantidad;
    long* pIter;

public:
    Lista(long* _iter) : capacidad(50), cantidad(0), pIter(_iter) {
        elementos = new T[capacidad];
    }
    ~Lista() { delete[] elementos; }

    void agregar(const T& e) {
        if (cantidad == capacidad) {
            capacidad *= 2;
            T* nuevo = new T[capacidad];
            for (int i = 0; i < cantidad; i++) {
                nuevo[i] = elementos[i];
                (*pIter)++;
            }
            delete[] elementos;
            elementos = nuevo;
        }
        elementos[cantidad++] = e;
        (*pIter)++;
    }

    T& obtener(int i) { return elementos[i]; }
    int size() const { return cantidad; }
};

#endif


partido.h

#ifndef PARTIDO_H
#define PARTIDO_H
#include "Equipo.h"

class Partido {
public:
    Equipo* e1;
    Equipo* e2;
    int golesE1;
    int golesE2;

    Partido();
    void simular(long& iteraciones, bool esEliminacion);
};

#endif
