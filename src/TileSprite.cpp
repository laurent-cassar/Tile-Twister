#include "TileSprite.hpp"
#include <string>

TTF_Font* TileSprite::font_ = nullptr;

TileSprite::TileSprite(int x, int y, int size, int value)
    : GameObject(x, y, size, size), value_(value) {}

TileSprite::~TileSprite() {}

void TileSprite::initFont(const std::string& fontPath) {
    if (!font_) {
        font_ = TTF_OpenFont(fontPath.c_str(), 48);
    }
}

void TileSprite::cleanupFont() {
    if (font_) {
        TTF_CloseFont(font_);
        font_ = nullptr;
    }
}

void TileSprite::render(SDL_Renderer* renderer) {
    // Dessiner le fond de la tuile
    SDL_Color bgColor = getColorForValue();
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(renderer, &rect_);
    
    // Dessiner le texte si la valeur n'est pas 0
    if (value_ > 0 && font_) {
        std::string text = std::to_string(value_);
        SDL_Color textColor = getTextColor();
        
        SDL_Surface* surface = TTF_RenderText_Blended(font_, text.c_str(), textColor);
        if (surface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture) {
                SDL_Rect textRect = {
                    rect_.x + (rect_.w - surface->w) / 2,
                    rect_.y + (rect_.h - surface->h) / 2,
                    surface->w,
                    surface->h
                };
                SDL_RenderCopy(renderer, texture, nullptr, &textRect);
                SDL_DestroyTexture(texture);
            }
            SDL_FreeSurface(surface);
        }
    }
}

void TileSprite::setValue(int value) {
    value_ = value;
}

SDL_Color TileSprite::getColorForValue() const {
    switch (value_) {
        case 0:    return { 205, 193, 180, 255 };
        case 2:    return { 238, 228, 218, 255 };
        case 4:    return { 237, 224, 200, 255 };
        case 8:    return { 242, 177, 121, 255 };
        case 16:   return { 245, 149, 99, 255 };
        case 32:   return { 246, 124, 95, 255 };
        case 64:   return { 246, 94, 59, 255 };
        case 128:  return { 237, 207, 114, 255 };
        case 256:  return { 237, 204, 97, 255 };
        case 512:  return { 237, 200, 80, 255 };
        case 1024: return { 237, 197, 63, 255 };
        case 2048: return { 237, 194, 46, 255 };
        default:   return { 60, 58, 50, 255 };
    }
}

SDL_Color TileSprite::getTextColor() const {
    if (value_ <= 4) {
        return { 119, 110, 101, 255 };
    }
    return { 249, 246, 242, 255 };
}