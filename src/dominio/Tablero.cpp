#include "../../include/dominio/Tablero.h"

Tablero::Tablero() {
    cantPiezasBlancas = 12;
    cantPiezasNegras = 12;
    cuadricula.resize(8, vector<Pieza*>(8, NULL));
}

Tablero::~Tablero() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (cuadricula[i][j] != NULL) {
                delete cuadricula[i][j];
                cuadricula[i][j] = NULL;
            }
        }
    }
}

void Tablero::inicializar() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cuadricula[i][j] = NULL;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 != 0) {
                cuadricula[i][j] = new PiezaNormal(NEGRO, i, j);
            }
        }
    }

    for (int i = 5; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 != 0) {
                cuadricula[i][j] = new PiezaNormal(BLANCO, i, j);
            }
        }
    }
}

Pieza* Tablero::getPieza(int fila, int columna) const {
    return cuadricula[fila][columna];
}

void Tablero::setPieza(int fila, int columna, Pieza* pieza) {
    cuadricula[fila][columna] = pieza;
}

void Tablero::moverPieza(int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {
    cuadricula[filaDestino][columnaDestino] = cuadricula[filaOrigen][columnaOrigen];
    cuadricula[filaOrigen][columnaOrigen] = NULL;
    cuadricula[filaDestino][columnaDestino]->setFila(filaDestino);
    cuadricula[filaDestino][columnaDestino]->setColumna(columnaDestino);
}

void Tablero::eliminarPieza(int fila, int columna) {
    if (cuadricula[fila][columna] != NULL) {
        if (cuadricula[fila][columna]->getColor() == BLANCO) {
            cantPiezasBlancas--;
        } else {
            cantPiezasNegras--;
        }
        delete cuadricula[fila][columna];
        cuadricula[fila][columna] = NULL;
    }
}

void Tablero::coronarPieza(int fila, int columna) {
    if (cuadricula[fila][columna] != NULL) {
        Color c = cuadricula[fila][columna]->getColor();
        delete cuadricula[fila][columna];
        cuadricula[fila][columna] = new Reina(c, fila, columna);
    }
}


int Tablero::getCantPiezasBlancas() const {
    return cantPiezasBlancas;
}

int Tablero::getCantPiezasNegras() const {
    return cantPiezasNegras;
}

bool Tablero::estaVacia(int fila, int columna) const {
    return cuadricula[fila][columna] == NULL;
}

bool Tablero::dentroDelTablero(int fila, int columna) const {
    return fila >= 0 && fila < 8 && columna >= 0 && columna < 8;
}
Tablero* Tablero::copiar() {
    Tablero* copia = new Tablero();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (!estaVacia(i, j)) {
                Pieza* pieza = getPieza(i, j);
                if (pieza->getEsReina()) {
                    copia->setPieza(i, j, new Reina(pieza->getColor(), i, j));
                } else {
                    copia->setPieza(i, j, new PiezaNormal(pieza->getColor(), i, j));
                }
            }
        }
    }
    copia->cantPiezasBlancas = cantPiezasBlancas;
    copia->cantPiezasNegras = cantPiezasNegras;
    return copia;
}
