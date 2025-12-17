#ifndef GAME_HPP
#define GAME_HPP

#include "Grid.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include <memory>

class Game {
public:
    Game();
    ~Game();
    
    void run();
    void restart();
    void save();
    void load();
    
private:
    void processInput();
    void update();
    void render();
    
    std::unique_ptr<Grid> grid_;
    std::unique_ptr<Window> window_;
    std::unique_ptr<Renderer> renderer_;
    
    bool running_;
    bool gameOver_;
};

#endif