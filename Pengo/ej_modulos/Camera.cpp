#include "Camera.h"



Camera::Camera() {

    // Set the view...
    view = new sf::View(sf::Vector2f(112.f, 104.f), sf::Vector2f(610.f, 506.f));
    view->zoom(0.4111067194);

    // Range of scroll...
    viewRange.x = 104.f;
    viewRange.y = 280.f - viewRange.x;
    pengoRange  = 25.0f;

}




Camera::~Camera() {
    delete view;
    view = NULL;
}




void Camera::Update(float pengoPosY) {
    sf::Vector2f _viewPosition = view->getCenter();

    // The view can do scroll inside a range
    if (_viewPosition.y >= viewRange.x  &&  _viewPosition.y <= viewRange.y) {
        
        // Pengo scroll...
        if (pengoPosY >= viewRange.x-pengoRange  &&  pengoPosY <= viewRange.y+pengoRange) {
            if (pengoPosY  >  _viewPosition.y + pengoRange) {
                view->setCenter(_viewPosition.x, pengoPosY-pengoRange);
            } else if (pengoPosY  <  _viewPosition.y - pengoRange) {
                view->setCenter(_viewPosition.x, pengoPosY+pengoRange);
            }
        }

        // Adjust view out of movement range...
        if (_viewPosition.y < viewRange.x) {
            view->setCenter(_viewPosition.x, viewRange.x);
        } else if (_viewPosition.y > viewRange.y) {
            view->setCenter(_viewPosition.x, viewRange.y);
        }
    }
}




sf::View Camera::getView() {
    return *view;
}