#include "Game.hpp"
#include <SDL2/SDL.h>

Game::Game() : running_(true), gameOver_(false) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Erreur initialisation SDL");
    }
    
    window_ = std::make_unique<Window>("2048 Game", 600, 700);
    renderer_ = std::make_unique<Renderer>(window_->getSDLRenderer());
    grid_ = std::make_unique<Grid>();
    
    TileSprite::initFont("assets/fonts/Arial.ttf");
}

Game::~Game() {
    TileSprite::cleanupFont();
    SDL_Quit();
}

void Game::run() {
    while (running_) {
        processInput();
        update();
        render();
        SDL_Delay(16); // ~60 FPS
    }
}

void Game::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running_ = false;
        } else if (event.type == SDL_KEYDOWN && !gameOver_) {
            bool moved = false;
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    moved = grid_->moveLeft();
                    break;
                case SDLK_RIGHT:
                    moved = grid_->moveRight();
                    break;
                case SDLK_UP:
                    moved = grid_->moveUp();
                    break;
                case SDLK_DOWN:
                    moved = grid_->moveDown();
                    break;
                case SDLK_r:
                    restart();
                    break;
            }
            
            if (moved && !grid_->canMove()) {
                gameOver_ = true;
            }
        }
    }
}

void Game::update() {
    // Logique de mise à jour si nécessaire
}

void Game::render() {
    window_->clear();
    renderer_->renderGrid(grid_.get());
    window_->present();
}

void Game::restart() {
    grid_->reset();
    gameOver_ = false;
}