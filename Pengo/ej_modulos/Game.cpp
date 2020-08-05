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
    window            = new sf::RenderWindow(sf::VideoMode(610.f, 506.f), "MSX-Pengo FV");
    camera            = new Camera();
    restartLevelClock = new sf::Clock();
    pengo             = new Pengo(&spriteSheet, 45.0f, 0.2f, sf::Vector2u(0,0), sf::Vector2i(6,6));
    currentLevel      = 0;
    level             = NULL;
    state             = change;
    window->setFramerateLimit(60);

    // Start game loop...
    GameLoop();

}



Game::~Game() {
    delete pengo;
    delete camera;
    delete window;
    delete restartLevelClock;
    for (Level* lvl : levels)
        delete lvl;
    levels.clear();
    pengo             = NULL;
    restartLevelClock = NULL;
    camera            = NULL;
    window            = NULL;
    level             = NULL;
}



void Game::GameLoop() {

    while (window->isOpen()) {
        deltaTime = clock.restart().asSeconds();

        // Events loop...
        if (!pengo->getStunned())
            EventsLoop();


        switch (state) {

            case play:  // Update all game

                // Change state
                if (pengo->getStunned())
                    state = stun;
                else if (level->completed())
                    state = change;
                break;


            case stun:  // Pengo is stunned

                if (restartLevelClock->getElapsedTime().asSeconds() > RESTART_TRANSITION_TIME) {
                    if (pengo->getGodMode()) {
                        pengo->restartPosition(deltaTime);
                    } else {
                        level->restart();
                        pengo->restartInitialState(deltaTime);
                        camera->restartPosition();
                    }
                    state = play;
                }
                break;


            case change:  // Next level
                Level* _new_level;

                // Create the new level
                currentLevel++;
                _new_level = new Level(&spriteSheet, &tileset, pengo, restartLevelClock);
                level = _new_level;
                levels.push_back(level); // Save the level for restarting

                // Go back to the initial view
                pengo->restartInitialState(deltaTime);
                camera->restartPosition();
                _new_level = NULL;
                state = play;
                break;
        }


        // Update all game...
        level->Update(deltaTime);
        camera->Update(pengo->getSprite()->getPosition().y);


        // Draw all the objects...
        Render();
    }

    // Break free all memory...
    delete gameInstance;
    gameInstance = NULL;
}



void Game::EventsLoop() {


    // Input for Pengo action
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        level->inputPlayer(0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        level->inputPlayer(1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        level->inputPlayer(2);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        level->inputPlayer(3);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        level->inputPlayer(4);


    // Input for global game
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

                    // Active god mode
                    case sf::Keyboard::G:
                        pengo->changeGodMode(window, deltaTime);
                        break;

                    case sf::Keyboard::X:
                        level->restart();
                        pengo->restartInitialState(deltaTime);
                        pengo->restoreLifes();
                        camera->restartPosition();
                        break;

                    case sf::Keyboard::N:
                        state = change;
                        break;

                    default:
                        // std::cout << "No key handled..." << std::endl;
                        break;
                }
                break;

            default:
                // std::cout << "No event handled..." << std::endl;
                break;
        }
    }
}




void Game::Render() {

    // Clear viewport...
    window->clear(sf::Color::Black);

    // Print level objects...
    level->Draw(*window);
    window->setView(camera->getView());

    // Display them on it...
    window->display();
}


