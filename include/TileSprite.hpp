#ifndef TILESPRITE_HPP
#define TILESPRITE_HPP

#include "GameObject.hpp"
#include <SDL2/SDL_ttf.h>
#include <string>

class TileSprite : public GameObject {
public:
    TileSprite(int x, int y, int size, int value);
    ~TileSprite() override;
    
    void render(SDL_Renderer* renderer) override;
    void setValue(int value);
    
    static void initFont(const std::string& fontPath);
    static void cleanupFont();
    
private:
    int value_;
    SDL_Color getColorForValue() const;
    SDL_Color getTextColor() const;
    
    static TTF_Font* font_;
};

#endif