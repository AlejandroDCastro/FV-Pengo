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
        {0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 2, 1, 0},
        {0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0},
        {0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0},
        {0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0},
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
    camera          = new Camera();
    labyrinth1      = new Labyrinth(&tileset, level1);
    labyrinth2      = new Labyrinth(&tileset, level2);
    labyrinth       = labyrinth1;
    pengo           = new Pengo(&spriteSheet, 45.0f, 0.2f, sf::Vector2u(0,0), sf::Vector2i(6,6));
    this->addSwarm(level1);
    collision       = new Collision();
    snoBeesPerLevel = 8;

    // Start game loop...
    GameLoop();
}



Game::~Game() {
    delete pengo;
    for (SnoBee* snobee : swarm) {
        delete snobee;
    }
    delete collision;
    swarm.clear();
    delete labyrinth1;
    delete labyrinth2;
    delete camera;
    delete window;
    delete gameInstance;
 //   delete clock;
//    delete levelClock;
    pengo        = NULL;
    labyrinth    = NULL;
    labyrinth1   = NULL;
    labyrinth2   = NULL;
    camera       = NULL;
    window       = NULL;
    gameInstance = NULL;
    collision    = NULL;
  //  clock        = NULL;
  //  levelClock   = NULL;
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
        for (SnoBee* snobee : swarm) {
            if (snobee  &&  !snobee->getDead()) {
                snobee->Update(deltaTime, labyrinth);

                // Check collision snobee-pengo
                if (collision->checkCollision(snobee->getSprite(), pengo->getSprite(), 10.0f))
                    pengo->loseLife();

                // Check collision snobee-block
                for (unsigned int i=0; i<size.x; i++) {
                    Block* _block;
                    for (unsigned int j=0; j<size.y; j++) {
                        _block = labyrinth->getBlock(i, j);

                        // If we smashes Sno-Bee add other one
                        if (_block  &&  _block->getDirection() > -1  &&  snobee->getFree()  &&  collision->checkCollision(_block->getSprite(), snobee->getSprite(), 20.f)) {
                            snobee->getSmashed(_block);
                            this->addSnoBee();
                        }
                        _block = NULL;
                    }
                }
            }
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



void Game::Draw() {

    // Clear viewport...
    window->clear(sf::Color::Black);

    // Print objects...
    labyrinth->Draw(*window);
    pengo->Draw(*window);
    for (SnoBee* snobee : swarm) {
        if (snobee  &&  !snobee->getDead())
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
                swarm.push_back(new SnoBee(&spriteSheet, 45.0f, 0.3f, sf::Vector2u(0, 2), sf::Vector2i(i, j)));
            }
        }
    }
}



// Add new Sno-Bees for replacing the old smashed
void Game::addSnoBee() {

    if (swarm.size() < snoBeesPerLevel) {
        sf::Vector2i _newPosition = labyrinth->getFreePosition();

        swarm.push_back(new SnoBee(&spriteSheet, 45.0f, 0.3f, sf::Vector2u(0, 2), _newPosition));
    }
}