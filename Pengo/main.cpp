#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/config.h"
#include "ej_modulos/Animation.h"

#define kVel 5

int main() {

  //Creamos una ventana
  sf::RenderWindow window(sf::VideoMode(640, 480), "MSX Pengo");

  //Cargo la imagen donde reside la textura del sprite
  sf::Texture tex;
  if (!tex.loadFromFile("resources/Pengos-Sno-Bees.png")) {
    std::cerr << "Error cargando la imagen sprites.png";
    exit(0);
  }

  //Y creo el spritesheet a partir de la imagen anterior
  sf::Sprite sprite(tex), sprite2(tex);

  Animation animation(&tex, sf::Vector2u(2,3), 1.0f, 2);
  sprite.setOrigin(animation.getOrigin());

  Animation animation2(&tex, sf::Vector2u(2,3), 1.0f, 6);
  sprite2.setOrigin(animation.getOrigin());

  // Lo dispongo en el centro de la pantalla
  sprite.setPosition(320, 240);
  sprite2.setPosition(400, 240);
  sf::Clock clock;
  //Bucle del juego
  while (window.isOpen()) {
    float deltaTime = clock.restart().asSeconds();
    //Bucle de obtención de eventos
    sf::Event event;
    while (window.pollEvent(event)) {
      

      switch (event.type) {

      //Si se recibe el evento de cerrar la ventana la cierro
      case sf::Event::Closed:
        window.close();
        break;

      //Se pulsó una tecla, imprimo su codigo
      case sf::Event::KeyPressed:

        //Verifico si se pulsa alguna tecla de movimiento
        switch (event.key.code) {

        //Mapeo del cursor
        case sf::Keyboard::Right:
          //Escala por defecto
          sprite.move(kVel, 0);
          break;

        case sf::Keyboard::Left:
          //Reflejo vertical
          sprite.move(-kVel, 0);
          break;

        case sf::Keyboard::Up:
          sprite.move(0, -kVel);
          break;

        case sf::Keyboard::Down:
          sprite.move(0, kVel);
          break;

        //Tecla ESC para salir
        case sf::Keyboard::Escape:
          window.close();
          break;

        //Cualquier tecla desconocida se imprime por pantalla su código
        default:
          std::cout << event.key.code << std::endl;
          break;
        }
      }
    }

    animation.Update(2, 2, deltaTime);
    sprite.setTextureRect(animation.getUVRect());

    animation2.Update(0, 0, deltaTime);
    sprite2.setTextureRect(animation2.getUVRect());

    window.clear();
    window.draw(sprite);
    window.draw(sprite2);
    window.display();
  }

  return 0;
}