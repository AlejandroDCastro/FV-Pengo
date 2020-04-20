#include "Game.h"



// Initialize pointer
Game* Game::gameInstance = NULL;


Game* Game::getInstance() {

    if (gameInstance == NULL) {
        gameInstance = new Game();
    }
    return gameInstance;
}



Game::Game() {

    // Loading textures...
    if (!spriteSheet.loadFromFile("resources/SpriteSheet.png")) {
        std::cout << "Failed loading sprite sheet..." << std::endl;
        exit(0);
    }
    if (!tileset.loadFromFile("resources/tileset.png")) {
        std::cout << "Failed loading tileset..." << std::endl;
        exit(0);
    }

    // Initialize variables...
    window    = new sf::RenderWindow(sf::VideoMode(610.f, 506.f), "MSX-Pengo FV");
    camera    = new Camera();
    labyrinth = new Labyrinth(&tileset);
    pengo     = new Pengo(&spriteSheet, 45.0f, 0.2f, sf::Vector2u(0,0), sf::Vector2i(0,0));
    abeja = new SnoBee(&spriteSheet, 45.0f, 0.2f, sf::Vector2u(4,3), sf::Vector2i(2,0), pengo->getDirPosition());

    // Start game loop...
    GameLoop();
}



Game::~Game() {
    delete pengo;
    delete labyrinth;
    delete camera;
    delete window;
    delete gameInstance;
    pengo        = NULL;
    labyrinth    = NULL;
    camera       = NULL;
    window       = NULL;
    gameInstance = NULL;
}



void Game::GameLoop() {

    while (window->isOpen()) {
        deltaTime = clock.restart().asSeconds();

        // Events loop...
        EventsLoop();

        // Update objects...
        pengo->Update(deltaTime, labyrinth);
        abeja->Update(deltaTime, labyrinth);
        camera->Update(pengo->getSprite()->getPosition().y);
        labyrinth->Update(deltaTime);


        // Draw all the objects...
        Draw();
    }
delete abeja;
abeja = NULL;
    // Free all memory
    delete gameInstance;
    gameInstance = NULL;
}



void Game::EventsLoop() {

    while (window->pollEvent(event)) {

        switch (event.type) {

            // Close the window manually
            case sf::Event::Closed:
                window->close();
                break;

            // Click one key...
            case sf::Event::KeyPressed:

                switch (event.key.code) {

                    // Close the window pressing escape
                    case sf::Keyboard::Escape:
                        window->close();
                        break;
                }
        }
    }
}



void Game::Draw() {

    // Clear viewport...
    window->clear(sf::Color::Black);

    // Print objects...
    labyrinth->Draw(*window);
    pengo->Draw(*window);
    abeja->Draw(*window);
    window->setView(camera->getView());

    // Display them on it...
    window->display();
}