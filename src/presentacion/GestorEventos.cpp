#define SFML_STATIC
#include "../../include/presentacion/GestorEventos.h"

GestorEventos::GestorEventos(sf::RenderWindow* vent, Partida* p, Renderer* r) {
    ventana = vent;
    partida = p;
    renderer = r;
    persistencia = new Persistencia();
    filaSeleccionada = -1;
    columnaSeleccionada = -1;
    hayPiezaSeleccionada = false;
    tamCelda = 100.0f;
    volverAlMenu = false;
}

GestorEventos::~GestorEventos() {
    delete persistencia;
}

void GestorEventos::procesarEventos() {
    sf::Event evento;
    while (ventana->pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            ventana->close();
        }

        if (evento.type == sf::Event::KeyPressed) {
            if (evento.key.code == sf::Keyboard::G) {
                persistencia->guardarPartida(partida, "partida.txt");
                renderer->limpiar();
                renderer->dibujarTablero();
                renderer->dibujarPiezas(partida->getTablero());
                renderer->dibujarInfo(partida);
                renderer->mostrar();
            }

            if (evento.key.code == sf::Keyboard::C) {
                persistencia->cargarPartida(partida, "partida.txt");
                hayPiezaSeleccionada = false;
                movimientosValidos.clear();
                renderer->limpiar();
                renderer->dibujarTablero();
                renderer->dibujarPiezas(partida->getTablero());
                renderer->dibujarInfo(partida);
                renderer->mostrar();
            }
        }

        if (evento.type == sf::Event::MouseButtonPressed) {
            if (evento.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f clickPos(evento.mouseButton.x, evento.mouseButton.y);

                sf::FloatRect areaCasita(745, 800, 40, 40);
                if (areaCasita.contains(clickPos)) {
                    volverAlMenu = true;
                    return;
                }

                sf::FloatRect areaBotonFin(250, 430, 300, 50);
                if (partida->isPartidaTerminada() && areaBotonFin.contains(clickPos)) {
                    volverAlMenu = true;
                    return;
                }

                if (partida->isPartidaTerminada()) return;

                int columna = evento.mouseButton.x / tamCelda;
                int fila = evento.mouseButton.y / tamCelda;

                if (fila < 0 || fila > 7 || columna < 0 || columna > 7) return;

                Tablero* tablero = partida->getTablero();
                ReglasJuego* reglas = partida->getReglas();
                Color colorActual = partida->getJugadorActual()->getColor();

                bool hayCapturaPosible = false;
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        if (!tablero->estaVacia(i, j) &&
                            tablero->getPieza(i, j)->getColor() == colorActual) {
                            if (reglas->hayCaptura(i, j)) {
                                hayCapturaPosible = true;
                                break;
                            }
                        }
                    }
                    if (hayCapturaPosible) break;
                }

                if (!hayPiezaSeleccionada) {
                    Pieza* pieza = tablero->getPieza(fila, columna);
                    if (pieza != NULL && pieza->getColor() == colorActual) {
                        if (hayCapturaPosible && !reglas->hayCaptura(fila, columna)) {
                            return;
                        }
                        filaSeleccionada = fila;
                        columnaSeleccionada = columna;
                        hayPiezaSeleccionada = true;
                        movimientosValidos = reglas->getMovimientosValidos(fila, columna);
                    }
                } else {
                    if (movimientosValidos.find(make_pair(fila, columna)) != movimientosValidos.end()) {
                        partida->realizarMovimiento(filaSeleccionada, columnaSeleccionada, fila, columna);
                        hayPiezaSeleccionada = false;
                        movimientosValidos.clear();

                        if (!partida->isPartidaTerminada() &&
                            partida->getJugadorActual()->esCPU()) {
                            Cpu* cpu = dynamic_cast<Cpu*>(partida->getJugadorActual());
                            if (cpu != NULL) {
                                cpu->realizarMovimiento();

                                if (reglas->juegoTerminado(partida->getJugadorActual()->getColor())) {
                                    partida->setPartidaTerminadaCPU(partida->getJugadorActual()->getNombre());
                                } else {
                                    partida->cambiarTurno();
                                }
                            }
                        }
                    } else {
                        Pieza* pieza = tablero->getPieza(fila, columna);
                        if (pieza != NULL && pieza->getColor() == colorActual) {
                            if (hayCapturaPosible && !reglas->hayCaptura(fila, columna)) {
                                return;
                            }
                            filaSeleccionada = fila;
                            columnaSeleccionada = columna;
                            movimientosValidos = reglas->getMovimientosValidos(fila, columna);
                        } else {
                            hayPiezaSeleccionada = false;
                            movimientosValidos.clear();
                        }
                    }
                }

                renderer->limpiar();
                renderer->dibujarTablero();
                renderer->dibujarMovimientosValidos(movimientosValidos);
                renderer->dibujarPiezas(partida->getTablero());
                renderer->dibujarInfo(partida);

                if (partida->isPartidaTerminada()) {
                    renderer->dibujarPantallaFin(partida->getGanador());
                }

                renderer->mostrar();
            }
        }
    }
}

bool GestorEventos::quiereVolverAlMenu() const {
    return volverAlMenu;
}

bool GestorEventos::juegoActivo() const {
    return ventana->isOpen();
}
