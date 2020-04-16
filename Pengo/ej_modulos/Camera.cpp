#include "Camera.h"



Camera::Camera(sf::Vector2f center, sf::Vector2f size) : view(center, size) {

}




Camera::~Camera() {

}




sf::View Camera::getView() {
    return view;
}