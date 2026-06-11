#include "../../include/presentacion/Confeti.h"

Confeti::Confeti() {
    cantParticulas = 150;
    srand(time(0));
}

Confeti::~Confeti() {
}

void Confeti::iniciar() {
    particulas.clear();

    sf::Color colores[] = {
        sf::Color(255, 50, 50),
        sf::Color(50, 255, 50),
        sf::Color(50, 50, 255),
        sf::Color(255, 255, 50),
        sf::Color(255, 50, 255),
        sf::Color(50, 255, 255),
        sf::Color(255, 165, 0)
    };

    for (int i = 0; i < cantParticulas; i++) {
        Particula p;
        p.forma.setSize(sf::Vector2f(8 + rand() % 6, 4 + rand() % 4));
        p.forma.setPosition(rand() % 800, -(rand() % 400));
        p.forma.setFillColor(colores[rand() % 7]);
        p.forma.setRotation(rand() % 360);
        p.velocidadX = -1.5f + (rand() % 30) / 10.0f;
        p.velocidadY = 2.0f + (rand() % 30) / 10.0f;
        p.velocidadRotacion = -3.0f + (rand() % 60) / 10.0f;
        particulas.push_back(p);
    }
}

void Confeti::actualizar() {
    for (int i = 0; i < particulas.size(); i++) {
        particulas[i].forma.move(particulas[i].velocidadX, particulas[i].velocidadY);
        particulas[i].forma.rotate(particulas[i].velocidadRotacion);

        if (particulas[i].forma.getPosition().y > 860) {
            particulas[i].forma.setPosition(rand() % 800, -10);
        }
    }
}

void Confeti::dibujar(sf::RenderWindow* ventana) {
    for (int i = 0; i < particulas.size(); i++) {
        ventana->draw(particulas[i].forma);
    }
}
