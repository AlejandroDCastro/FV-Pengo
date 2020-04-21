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

    // Create labyrinth structure for two levels...
    size.x = 15;
    size.y = 13;
    int level1[15][13] = {
        {0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0},
        {0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0},
        {0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0},
        {0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 2, 1, 0, 1, 0, 0, 0, 0},
        {1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0},
        {0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 2, 1, 0},
        {0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0},
        {2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}
    };
    int level2[15][13] = {
        {0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0},
        {0, 1, 2, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 2},
        {0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 2, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}
    };

    // Initialize variables...
    window     = new sf::RenderWindow(sf::VideoMode(610.f, 506.f), "MSX-Pengo FV");
    window->setFramerateLimit(60);
    camera     = new Camera();
    labyrinth1 = new Labyrinth(&tileset, level1);
    labyrinth2 = new Labyrinth(&tileset, level2);
    labyrinth  = labyrinth2;
    pengo      = new Pengo(&spriteSheet, 45.0f, 0.2f, sf::Vector2u(0,0), sf::Vector2i(6,6));
    this->addSwarm(level1);
   // abeja = new SnoBee(&spriteSheet, 30.0f, 0.2f, sf::Vector2u(0,2), sf::Vector2i(5,3));

    // Start game loop...
    GameLoop();
}



Game::~Game() {
    delete pengo;
    for (SnoBee* snobee : swarm) {
        delete snobee;
    }
    swarm.clear();
    delete labyrinth1;
    delete labyrinth2;
    delete camera;
    delete window;
    delete gameInstance;
    pengo        = NULL;
    labyrinth    = NULL;
    labyrinth1   = NULL;
    labyrinth2   = NULL;
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
        camera->Update(pengo->getSprite()->getPosition().y);
        labyrinth->Update(deltaTime);
     //   abeja->Update(deltaTime, labyrinth);
        for (SnoBee* snobee : swarm) {
            snobee->Update(deltaTime, labyrinth);
        }


        // Draw all the objects...
        Draw();
    }

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
    for (SnoBee* snobee : swarm) {
        snobee->Draw(*window);
    }
   // abeja->Draw(*window);
    window->setView(camera->getView());

    // Display them on it...
    window->display();
}



// Create the sno-bees for level
void Game::addSwarm(int level[15][13]) {

    for (int i=0; i<15; i++) {
        for (int j=0; j<13; j++) {
            if (level[i][j] == 2) {
                swarm.push_back(new SnoBee(&spriteSheet, 30.0f, 0.3f, sf::Vector2u(0, 2), sf::Vector2i(i, j)));
            }
        }
    }
}