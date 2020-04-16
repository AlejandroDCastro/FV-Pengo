#pragma once
#include <SFML/Graphics.hpp>


class Camera {

    private:
        sf::View view;


    public:
        Camera(sf::Vector2f, sf::Vector2f );
        ~Camera();
        void Update(); // falta ver el factor de multiplicacion al hacer zoom
        sf::View getView();

};