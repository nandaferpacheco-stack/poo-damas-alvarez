#include "../../include/dominio/Jugador.h"

Jugador::Jugador(string nom, Color c) {
    nombre = nom;
    color = c;
    piezasCapturadas = 0;
}

Jugador::~Jugador() {
}

string Jugador::getNombre() const {
    return nombre;
}

Color Jugador::getColor() const {
    return color;
}

int Jugador::getPiezasCapturadas() const {
    return piezasCapturadas;
}

void Jugador::aumentarPiezasCapturadas() {
    piezasCapturadas++;
}

bool Jugador::esCPU() const {
    return false;
}