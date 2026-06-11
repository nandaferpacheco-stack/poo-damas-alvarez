#include "../../include/logica/Partida.h"

Partida::Partida(Jugador* j1, Jugador* j2) {
    jugador1 = j1;
    jugador2 = j2;
    jugadorActual = j1;
    tablero = new Tablero();
    reglas = new ReglasJuego(tablero);
    partidaTerminada = false;
    ganador = "";
    estadisticas[j1->getNombre()] = 0;
    if (j2 != NULL) {
        estadisticas[j2->getNombre()] = 0;
    }
}

Partida::~Partida() {
    delete tablero;
    delete reglas;
}

void Partida::iniciar() {
    tablero->inicializar();
    partidaTerminada = false;
    ganador = "";
    jugadorActual = jugador1;
}

bool Partida::realizarMovimiento(int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {
    if (partidaTerminada) return false;
    Pieza* pieza = tablero->getPieza(filaOrigen, columnaOrigen);
    if (pieza == NULL) return false;
    if (pieza->getColor() != jugadorActual->getColor()) return false;
    bool movimientoRealizado = reglas->realizarMovimiento(filaOrigen, columnaOrigen, filaDestino, columnaDestino);
    if (movimientoRealizado) {
        if (reglas->juegoTerminado(jugadorActual->getColor())) {
            partidaTerminada = true;
            ganador = jugadorActual->getNombre();
            estadisticas[jugadorActual->getNombre()]++;
            return true;
        }
        cambiarTurno();
    }
    return movimientoRealizado;
}

void Partida::setJugador2(Jugador* j2) {
    jugador2 = j2;
    estadisticas[j2->getNombre()] = 0;
}

void Partida::cambiarTurno() {
    if (jugadorActual == jugador1) {
        jugadorActual = jugador2;
    } else {
        jugadorActual = jugador1;
    }
}

Jugador* Partida::getJugadorActual() const {
    return jugadorActual;
}

Jugador* Partida::getJugador1() const {
    return jugador1;
}

Jugador* Partida::getJugador2() const {
    return jugador2;
}

Tablero* Partida::getTablero() const {
    return tablero;
}

ReglasJuego* Partida::getReglas() const {
    return reglas;
}

map<string, int> Partida::getEstadisticas() const {
    return estadisticas;
}

bool Partida::isPartidaTerminada() const {
    return partidaTerminada;
}

string Partida::getGanador() const {
    return ganador;
}

void Partida::setPartidaTerminadaCPU(string nombreGanador) {
    partidaTerminada = true;
    ganador = nombreGanador;
    estadisticas[nombreGanador]++;
}
