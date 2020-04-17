#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/config.h"
#include "ej_modulos/Pengo.h"
#include "ej_modulos/Character.h"
#include "ej_modulos/IceBlock.h"
#include "ej_modulos/Block.h"
#include "ej_modulos/Labyrinth.h"
#include "ej_modulos/Animation.h"
#include "ej_modulos/Camera.h"

#define kVel 5

int main() {

  //Creamos una ventana
 /* sf::RenderWindow window(sf::VideoMode(284, 208), "MSX Pengo");
  sf::View vista(sf::Vector2f(112.f, 148.f), sf::Vector2f(284.f, 208.f));*/

  sf::RenderWindow window(sf::VideoMode(610.f, 506.f), "MSX Pengo");
  Camera *camera = new Camera();
  

 
  //Cargo la imagen donde reside la textura del sprite
  sf::Texture tex, tex2;
  if (!tex.loadFromFile("resources/SpriteSheet.png")) {
    std::cerr << "Error cargando la imagen sprites.png";
    exit(0);
  }
  tex2.loadFromFile("resources/tileset.png");
 // tex.setSmooth(true);
  //tex2.setSmooth(true);

  Labyrinth *laberinto = new Labyrinth(&tex2);
  Pengo *pengo = new Pengo(&tex, 45.0f, 0.2f, sf::Vector2u(0,0), sf::Vector2u(0,0));

  //Y creo el spritesheet a partir de la imagen anterior
  sf::Sprite sprite(tex), sprite2(tex);


  // Lo dispongo en el centro de la pantalla
 
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
          case sf::Keyboard::F:
          pengo->loseLife();
          break;

          case sf::Keyboard::Escape:
          window.close();
          break;
        }

      }
    }

    pengo->Update(deltaTime);
    camera->Update(pengo->getSprite()->getPosition().y);

    window.clear();
    laberinto->Draw(window);
    pengo->Draw(window);
    window.setView(camera->getView());
    window.display();
  }

  delete laberinto;
  laberinto = NULL;
  delete pengo;
  pengo = NULL;
  delete camera;
  camera = NULL;


  return 0;
}