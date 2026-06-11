#include "../../include/logica/ReglasJuego.h"

ReglasJuego::ReglasJuego(Tablero* t) {
    tablero = t;
}

ReglasJuego::~ReglasJuego() {
}

set<pair<int,int>> ReglasJuego::getMovimientosValidos(int fila, int columna) {
    set<pair<int,int>> movimientos;
    Pieza* pieza = tablero->getPieza(fila, columna);

    if (pieza == NULL) return movimientos;

    int direcciones[4][2] = {{-1,-1},{-1,1},{1,-1},{1,1}};
    set<pair<int,int>> capturas;

    if (pieza->getEsReina()) {
        for (int i = 0; i < 4; i++) {
            int f = fila + direcciones[i][0];
            int c = columna + direcciones[i][1];
            bool encontroEnemigo = false;

            while (tablero->dentroDelTablero(f, c)) {
                if (!tablero->estaVacia(f, c)) {
                    if (!encontroEnemigo &&
                        tablero->getPieza(f, c)->getColor() != pieza->getColor()) {
                        encontroEnemigo = true;
                    } else {
                        break;
                    }
                } else if (encontroEnemigo) {
                    capturas.insert(make_pair(f, c));
                    break;
                }
                f += direcciones[i][0];
                c += direcciones[i][1];
            }
        }

        if (!capturas.empty()) return capturas;

        for (int i = 0; i < 4; i++) {
            int f = fila + direcciones[i][0];
            int c = columna + direcciones[i][1];
            while (tablero->dentroDelTablero(f, c) && tablero->estaVacia(f, c)) {
                movimientos.insert(make_pair(f, c));
                f += direcciones[i][0];
                c += direcciones[i][1];
            }
        }

    } else {
        for (int i = 0; i < 4; i++) {
            int filaMedio = fila + direcciones[i][0];
            int colMedio = columna + direcciones[i][1];
            int filaDestino = fila + 2 * direcciones[i][0];
            int colDestino = columna + 2 * direcciones[i][1];

            if (!tablero->dentroDelTablero(filaMedio, colMedio)) continue;
            if (!tablero->dentroDelTablero(filaDestino, colDestino)) continue;
            if (tablero->estaVacia(filaMedio, colMedio)) continue;
            if (tablero->getPieza(filaMedio, colMedio)->getColor() == pieza->getColor()) continue;
            if (!tablero->estaVacia(filaDestino, colDestino)) continue;
            if (!pieza->puedeMoverse(filaMedio, colMedio)) continue;

            capturas.insert(make_pair(filaDestino, colDestino));
        }

        if (!capturas.empty()) return capturas;

        for (int i = 0; i < 4; i++) {
            int filaDestino = fila + direcciones[i][0];
            int colDestino = columna + direcciones[i][1];

            if (!tablero->dentroDelTablero(filaDestino, colDestino)) continue;
            if (!tablero->estaVacia(filaDestino, colDestino)) continue;
            if (!pieza->puedeMoverse(filaDestino, colDestino)) continue;

            movimientos.insert(make_pair(filaDestino, colDestino));
        }
    }

    return movimientos;
}

bool ReglasJuego::hayCaptura(int fila, int columna) {
    Pieza* pieza = tablero->getPieza(fila, columna);
    if (pieza == NULL) return false;

    int direcciones[4][2] = {{-1,-1},{-1,1},{1,-1},{1,1}};
    for (int i = 0; i < 4; i++) {
        int filaMedio = fila + direcciones[i][0];
        int colMedio = columna + direcciones[i][1];
        int filaDestino = fila + 2 * direcciones[i][0];
        int colDestino = columna + 2 * direcciones[i][1];

        if (!tablero->dentroDelTablero(filaMedio, colMedio)) continue;
        if (!tablero->dentroDelTablero(filaDestino, colDestino)) continue;
        if (tablero->estaVacia(filaMedio, colMedio)) continue;
        if (tablero->getPieza(filaMedio, colMedio)->getColor() == pieza->getColor()) continue;
        if (!tablero->estaVacia(filaDestino, colDestino)) continue;

        if (!pieza->getEsReina()) {
            if (!pieza->puedeMoverse(filaMedio, colMedio)) continue;
        }

        return true;
    }
    return false;
}

bool ReglasJuego::hayCapturaPosible(Color color) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (!tablero->estaVacia(i, j) &&
                tablero->getPieza(i, j)->getColor() == color) {
                if (hayCaptura(i, j)) return true;
            }
        }
    }
    return false;
}

bool ReglasJuego::realizarMovimiento(int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {
    set<pair<int,int>> movimientos = getMovimientosValidos(filaOrigen, columnaOrigen);

    if (movimientos.find(make_pair(filaDestino, columnaDestino)) == movimientos.end()) {
        return false;
    }

    int difFila = filaDestino - filaOrigen;
    int difColumna = columnaDestino - columnaOrigen;

    if (!tablero->getPieza(filaOrigen, columnaOrigen)->getEsReina()) {
        if (difFila == 2 || difFila == -2) {
            int filaMedio = filaOrigen + difFila / 2;
            int colMedio = columnaOrigen + difColumna / 2;
            tablero->eliminarPieza(filaMedio, colMedio);
        }
    } else {
        int dirFila = (difFila > 0) ? 1 : -1;
        int dirCol = (difColumna > 0) ? 1 : -1;
        int f = filaOrigen + dirFila;
        int c = columnaOrigen + dirCol;
        while (f != filaDestino && c != columnaDestino) {
            if (!tablero->estaVacia(f, c)) {
                tablero->eliminarPieza(f, c);
                break;
            }
            f += dirFila;
            c += dirCol;
        }
    }

    tablero->moverPieza(filaOrigen, columnaOrigen, filaDestino, columnaDestino);
    verificarCorona(filaDestino, columnaDestino);

    return true;
}

bool ReglasJuego::verificarCorona(int fila, int columna) {
    Pieza* pieza = tablero->getPieza(fila, columna);
    if (pieza == NULL) return false;

    if (pieza->getColor() == BLANCO && fila == 0) {
        tablero->coronarPieza(fila, columna);
        return true;
    }

    if (pieza->getColor() == NEGRO && fila == 7) {
        tablero->coronarPieza(fila, columna);
        return true;
    }

    return false;
}

bool ReglasJuego::juegoTerminado(Color colorTurno) {
    if (tablero->getCantPiezasBlancas() == 0 ||
        tablero->getCantPiezasNegras() == 0) {
        return true;
    }

    Color colorRival = (colorTurno == BLANCO) ? NEGRO : BLANCO;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (!tablero->estaVacia(i, j) &&
                tablero->getPieza(i, j)->getColor() == colorRival) {
                if (!getMovimientosValidos(i, j).empty()) {
                    return false;
                }
            }
        }
    }
    return true;
}

Color ReglasJuego::getGanador() {
    if (tablero->getCantPiezasBlancas() == 0) return NEGRO;
    if (tablero->getCantPiezasNegras() == 0) return BLANCO;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (!tablero->estaVacia(i, j) &&
                tablero->getPieza(i, j)->getColor() == BLANCO) {
                if (!getMovimientosValidos(i, j).empty()) {
                    return BLANCO;
                }
            }
        }
    }
    return NEGRO;
}
