#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <string>

class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();
    
    SDL_Window* getSDLWindow() const { return window_; }
    SDL_Renderer* getSDLRenderer() const { return renderer_; }
    
    void clear();
    void present();
    
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    
private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    int width_;
    int height_;
};

#endif