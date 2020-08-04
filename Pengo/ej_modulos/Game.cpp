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
    state             = play;
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
        EventsLoop();

/*
        switch (state) {

            case play:  // Update all game

                level->Update(deltaTime);
                camera->Update(pengo->getSprite()->getPosition().y);

                // Change state
                if (pengo->getStunned())
                    state = stun;
                else if (level->completed())
                    state = next;
                break;

            case stun:  // Pengo is stunned

                break;

            case next:  // Next level

                if ()
                break;
        }*/

        if (pengo->getDead())
            window->close();

        // Check if the current level has been completed and go to the next
        if (currentLevel == 0  ||  level->completed()) {
            Level* _new_level;
            currentLevel++;

            // Close the window...
            if (currentLevel == TOTAL_LEVELS)
                window->close();

            _new_level = new Level(&spriteSheet, &tileset, pengo, restartLevelClock);
                
            level = _new_level;
            levels.push_back(level);

            pengo->restartInitialState(deltaTime);
            camera->restartPosition();
            _new_level = NULL;
        } else {
            
            if (pengo->getStunned()  &&  restartLevelClock->getElapsedTime().asSeconds() > RESTART_TRANSITION_TIME) {
             /*   if (currentLevel == 1)
                    level->restart(&spriteSheet, &tileset, 1);
                else
                    level->restart(&spriteSheet, &tileset, 2);*/

                if (pengo->getGodMode()) {
                    pengo->restartPosition();
                } else {
                    pengo->restartInitialState(deltaTime);
                    camera->restartPosition();
                }

            }

            level->Update(deltaTime);
            camera->Update(pengo->getSprite()->getPosition().y);
        }

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
/*
                    case sf::Keyboard::X:
                        pengo->restoreLifes();
                        break;

                    case sf::Keyboard::N:
                        if (level == 1) {
                            level = 2;
                            restore level
                        }
                        break;
*/
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


