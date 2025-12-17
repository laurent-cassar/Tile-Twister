#include "Window.hpp"
#include <stdexcept>

Window::Window(const std::string& title, int width, int height)
    : width_(width), height_(height) {
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("SDL initialization failed: " + std::string(SDL_GetError()));
    }
    
    window_ = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );
    
    if (!window_) {
        SDL_Quit();
        throw std::runtime_error("Window creation failed: " + std::string(SDL_GetError()));
    }
    
    renderer_ = SDL_CreateRenderer(
        window_,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    
    if (!renderer_) {
        SDL_DestroyWindow(window_);
        SDL_Quit();
        throw std::runtime_error("Renderer creation failed: " + std::string(SDL_GetError()));
    }
}

Window::~Window() {
    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
    }
    if (window_) {
        SDL_DestroyWindow(window_);
    }
}

void Window::clear() {
    SDL_SetRenderDrawColor(renderer_, 250, 248, 239, 255); // Couleur de fond beige
    SDL_RenderClear(renderer_);
}

void Window::present() {
    SDL_RenderPresent(renderer_);
}