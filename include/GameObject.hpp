#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SDL2/SDL.h>

class GameObject {
public:
    GameObject(int x, int y, int width, int height);
    virtual ~GameObject() = default;
    
    virtual void render(SDL_Renderer* renderer) = 0;
    
    void setPosition(int x, int y);
    void setSize(int width, int height);
    
    SDL_Rect getRect() const { return rect_; }
    
protected:
    SDL_Rect rect_;
};

#endif