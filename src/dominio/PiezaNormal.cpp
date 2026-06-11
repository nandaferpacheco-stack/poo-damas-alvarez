#include "../../include/dominio/PiezaNormal.h"

PiezaNormal::PiezaNormal(Color c, int f, int col) : Pieza(c, f, col) {
}

PiezaNormal::~PiezaNormal() {
}

bool PiezaNormal::puedeMoverse(int filaDestino, int columnaDestino) const {
    int difFila = filaDestino - fila;
    int difColumna = columnaDestino - columna;

    if (difColumna != 1 && difColumna != -1) {
        return false;
    }

    if (color == BLANCO) {
        return difFila == -1;
    } else {
        return difFila == 1;
    }
}