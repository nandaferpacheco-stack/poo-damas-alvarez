#include "../../include/dominio/Pieza.h"

Pieza::Pieza(Color c, int f, int col) {
    color = c;
    fila = f;
    columna = col;
    esReina = false;
}

Pieza::~Pieza() {
}

Color Pieza::getColor() const {
    return color;
}

int Pieza::getFila() const {
    return fila;
}

int Pieza::getColumna() const {
    return columna;
}

bool Pieza::getEsReina() const {
    return esReina;
}

void Pieza::setFila(int nuevaFila) {
    fila = nuevaFila;
}

void Pieza::setColumna(int nuevaColumna) {
    columna = nuevaColumna;
}

void Pieza::setEsReina(bool valor) {
    esReina = valor;
}
