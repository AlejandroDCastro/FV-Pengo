#pragma once
#include <SFML/Graphics.hpp>



class Camera {

    private:
        sf::View *view;
        sf::Vector2f viewRange;     // Center of the view
        float pengoRange;           // Range of non-scrolling

    public:
        Camera();
        ~Camera();
        void Update(float );
        sf::View getView();

};