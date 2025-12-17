#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <vector>
#include "Grid.hpp"

class Renderer {
public:
    explicit Renderer(SDL_Renderer* renderer);
    ~Renderer();
    
    void renderGrid(const Grid* grid);
    void renderGameOver(int score);
    void renderVictory(int score);
    void renderScore(int score);
    
    void clear();
    void present();
    
private:
    SDL_Renderer* renderer_;
    TTF_Font* font_;
    TTF_Font* titleFont_;
    
    void renderTile(int value, int x, int y, int size);
    void renderText(const char* text, int x, int y, SDL_Color color, TTF_Font* font);
    SDL_Color getTileColor(int value) const;
    SDL_Color getTextColor(int value) const;
    
    static constexpr int GRID_PADDING = 20;
    static constexpr int TILE_SPACING = 15;
    static constexpr int TILE_SIZE = 120;
};

#endif // RENDERER_HPP