#include "../../include/presentacion/Menu.h"

Menu::Menu(sf::RenderWindow* vent) {
    ventana = vent;
    fuente.loadFromFile("D:/juego/assets/fuentes/arial.ttf");

    sf::Image imagen;
    imagen.loadFromFile("D:/juego/assets/imagenes/fondo.png");
    fondo.loadFromImage(imagen);
    spriteFondo.setTexture(fondo);

    float scaleX = 800.0f / fondo.getSize().x;
    float scaleY = 850.0f / fondo.getSize().y;
    spriteFondo.setScale(scaleX, scaleY);

    boton1.setSize(sf::Vector2f(260, 40));
    boton1.setPosition(270, 645);
    boton1.setFillColor(sf::Color(101, 67, 33, 100));
    boton1.setOutlineColor(sf::Color(180, 130, 70));
    boton1.setOutlineThickness(2);

    textoBoton1.setFont(fuente);
    textoBoton1.setCharacterSize(22);
    textoBoton1.setFillColor(sf::Color(255, 240, 200));
    textoBoton1.setString("Un Jugador");
    textoBoton1.setPosition(330, 650);

    boton2.setSize(sf::Vector2f(260, 40));
    boton2.setPosition(270, 700);
    boton2.setFillColor(sf::Color(101, 67, 33, 100));
    boton2.setOutlineColor(sf::Color(180, 130, 70));
    boton2.setOutlineThickness(2);

    textoBoton2.setFont(fuente);
    textoBoton2.setCharacterSize(22);
    textoBoton2.setFillColor(sf::Color(255, 240, 200));
    textoBoton2.setString("Dos Jugadores");
    textoBoton2.setPosition(310, 705);

    boton3.setSize(sf::Vector2f(260, 40));
    boton3.setPosition(270, 755);
    boton3.setFillColor(sf::Color(101, 67, 33, 100));
    boton3.setOutlineColor(sf::Color(180, 130, 70));
    boton3.setOutlineThickness(2);

    textoBoton3.setFont(fuente);
    textoBoton3.setCharacterSize(22);
    textoBoton3.setFillColor(sf::Color(255, 240, 200));
    textoBoton3.setString("Salir");
    textoBoton3.setPosition(355, 760);
}

Menu::~Menu() {
}

int Menu::mostrar() {
    while (ventana->isOpen()) {
        sf::Event evento;
        while (ventana->pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana->close();
                return -1;
            }

            if (evento.type == sf::Event::MouseButtonPressed) {
                if (evento.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f click(evento.mouseButton.x, evento.mouseButton.y);

                    if (boton1.getGlobalBounds().contains(click)) {
                        return 2;
                    }
                    if (boton2.getGlobalBounds().contains(click)) {
                        return 1;
                    }
                    if (boton3.getGlobalBounds().contains(click)) {
                        ventana->close();
                        return -1;
                    }
                }
            }

            if (evento.type == sf::Event::MouseMoved) {
                sf::Vector2f mouse(evento.mouseMove.x, evento.mouseMove.y);

                if (boton1.getGlobalBounds().contains(mouse)) {
                    boton1.setFillColor(sf::Color(160, 100, 40, 180));
                } else {
                    boton1.setFillColor(sf::Color(101, 67, 33, 100));
                }

                if (boton2.getGlobalBounds().contains(mouse)) {
                    boton2.setFillColor(sf::Color(160, 100, 40, 180));
                } else {
                    boton2.setFillColor(sf::Color(101, 67, 33, 100));
                }

                if (boton3.getGlobalBounds().contains(mouse)) {
                    boton3.setFillColor(sf::Color(160, 100, 40, 180));
                } else {
                    boton3.setFillColor(sf::Color(101, 67, 33, 100));
                }
            }
        }

        ventana->clear();
        ventana->draw(spriteFondo);
        ventana->draw(boton1);
        ventana->draw(textoBoton1);
        ventana->draw(boton2);
        ventana->draw(textoBoton2);
        ventana->draw(boton3);
        ventana->draw(textoBoton3);
        ventana->display();
    }

    return -1;
}
