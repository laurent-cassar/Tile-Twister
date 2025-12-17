#include "Renderer.hpp"
#include <string>
#include <stdexcept>

Renderer::Renderer(SDL_Renderer* renderer) : renderer_(renderer) {
    if (TTF_Init() < 0) {
        throw std::runtime_error("TTF initialization failed: " + std::string(TTF_GetError()));
    }
    
    // Charger les polices
    font_ = TTF_OpenFont("assets/fonts/Arial.ttf", 48);
    titleFont_ = TTF_OpenFont("assets/fonts/Arial.ttf", 72);
    
    if (!font_ || !titleFont_) {
        // Si Arial n'est pas disponible, essayer une police système
        font_ = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 48);
        titleFont_ = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 72);
        
        if (!font_ || !titleFont_) {
            TTF_Quit();
            throw std::runtime_error("Font loading failed: " + std::string(TTF_GetError()));
        }
    }
}

Renderer::~Renderer() {
    if (font_) TTF_CloseFont(font_);
    if (titleFont_) TTF_CloseFont(titleFont_);
    TTF_Quit();
}

void Renderer::renderGrid(const Grid* grid) {
    clear();
    
    // Afficher le score en haut
    renderScore(grid->getScore());
    
    // Calculer la position de départ de la grille
    int startX = GRID_PADDING;
    int startY = 120; // Laisser de l'espace pour le score
    
    // Dessiner le fond de la grille
    SDL_Rect gridBg = {
        startX - 10,
        startY - 10,
        (TILE_SIZE + TILE_SPACING) * Grid::SIZE + 10,
        (TILE_SIZE + TILE_SPACING) * Grid::SIZE + 10
    };
    SDL_SetRenderDrawColor(renderer_, 187, 173, 160, 255);
    SDL_RenderFillRect(renderer_, &gridBg);
    
    // Dessiner les tuiles
    for (int i = 0; i < Grid::SIZE; ++i) {
        for (int j = 0; j < Grid::SIZE; ++j) {
            int value = grid->getCell(i, j);
            int x = startX + j * (TILE_SIZE + TILE_SPACING);
            int y = startY + i * (TILE_SIZE + TILE_SPACING);
            
            renderTile(value, x, y, TILE_SIZE);
        }
    }
    
    present();
}

void Renderer::renderTile(int value, int x, int y, int size) {
    SDL_Rect tileRect = { x, y, size, size };
    
    // Couleur de fond de la tuile
    SDL_Color bgColor = getTileColor(value);
    SDL_SetRenderDrawColor(renderer_, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(renderer_, &tileRect);
    
    // Afficher le nombre si la tuile n'est pas vide
    if (value > 0) {
        std::string text = std::to_string(value);
        SDL_Color textColor = getTextColor(value);
        
        // Ajuster la taille de police selon la longueur du nombre
        TTF_Font* currentFont = (value < 100) ? titleFont_ : font_;
        if (value >= 1000) {
            currentFont = TTF_OpenFont("assets/fonts/Arial.ttf", 36);
            if (!currentFont) currentFont = font_;
        }
        
        renderText(text.c_str(), x + size/2, y + size/2, textColor, currentFont);
        
        if (value >= 1000 && currentFont != font_) {
            TTF_CloseFont(currentFont);
        }
    }
}

void Renderer::renderText(const char* text, int x, int y, SDL_Color color, TTF_Font* font) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    if (!surface) return;
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        return;
    }
    
    SDL_Rect destRect = {
        x - surface->w / 2,
        y - surface->h / 2,
        surface->w,
        surface->h
    };
    
    SDL_RenderCopy(renderer_, texture, nullptr, &destRect);
    
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Renderer::renderScore(int score) {
    SDL_Color scoreColor = { 119, 110, 101, 255 };
    
    // Titre "SCORE"
    renderText("SCORE", 100, 40, scoreColor, font_);
    
    // Valeur du score
    std::string scoreText = std::to_string(score);
    SDL_Color valueColor = { 255, 255, 255, 255 };
    
    // Fond du score
    SDL_Rect scoreBg = { 50, 60, 100, 50 };
    SDL_SetRenderDrawColor(renderer_, 187, 173, 160, 255);
    SDL_RenderFillRect(renderer_, &scoreBg);
    
    renderText(scoreText.c_str(), 100, 85, valueColor, font_);
}

void Renderer::renderGameOver(int score) {
    // Fond semi-transparent
    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 180);
    SDL_Rect overlay = { 0, 0, 600, 700 };
    SDL_RenderFillRect(renderer_, &overlay);
    
    // Message "Game Over"
    SDL_Color textColor = { 255, 255, 255, 255 };
    renderText("GAME OVER", 300, 250, textColor, titleFont_);
    
    // Score final
    std::string scoreText = "Score: " + std::to_string(score);
    renderText(scoreText.c_str(), 300, 350, textColor, font_);
    
    // Instructions
    renderText("Press R to restart", 300, 450, textColor, font_);
}

void Renderer::renderVictory(int score) {
    // Fond semi-transparent doré
    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer_, 237, 194, 46, 200);
    SDL_Rect overlay = { 0, 0, 600, 700 };
    SDL_RenderFillRect(renderer_, &overlay);
    
    // Message "You Win!"
    SDL_Color textColor = { 255, 255, 255, 255 };
    renderText("YOU WIN!", 300, 250, textColor, titleFont_);
    
    // Score final
    std::string scoreText = "Score: " + std::to_string(score);
    renderText(scoreText.c_str(), 300, 350, textColor, font_);
    
    // Instructions
    renderText("Press R to restart", 300, 450, textColor, font_);
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(renderer_, 250, 248, 239, 255);
    SDL_RenderClear(renderer_);
}

void Renderer::present() {
    SDL_RenderPresent(renderer_);
}

SDL_Color Renderer::getTileColor(int value) const {
    switch (value) {
        case 0:    return { 205, 193, 180, 255 }; // Vide
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
        default:   return { 60, 58, 50, 255 }; // Pour 4096+
    }
}

SDL_Color Renderer::getTextColor(int value) const {
    if (value <= 4) {
        return { 119, 110, 101, 255 }; // Texte foncé pour tuiles claires
    }
    return { 249, 246, 242, 255 }; // Texte clair pour tuiles foncées
}