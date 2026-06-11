#include "../../include/dominio/Reina.h"

Reina::Reina(Color c, int f, int col) : Pieza(c, f, col) {
    esReina = true;
}

Reina::~Reina() {
}

bool Reina::puedeMoverse(int filaDestino, int columnaDestino) const {
    int difFila = filaDestino - fila;
    int difColumna = columnaDestino - columna;

    if (difFila == 0 || difColumna == 0) {
        return false;
    }

    if (difFila < 0) difFila = -difFila;
    if (difColumna < 0) difColumna = -difColumna;

    return difFila == difColumna;
}
