#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <string>

class GameState {
public:
    enum class State {
        PLAYING,
        WON,
        GAME_OVER
    };
    
    GameState();
    
    State getState() const { return state_; }
    void setState(State state) { state_ = state; }
    
    int getScore() const { return score_; }
    void setScore(int score) { score_ = score; }
    void addScore(int points) { score_ += points; }
    
    int getBestScore() const { return bestScore_; }
    void updateBestScore();
    
    void reset();
    
    // Sauvegarde et chargement
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
    
private:
    State state_;
    int score_;
    int bestScore_;
    
    void loadBestScore();
    void saveBestScore() const;
};

#endif // GAMESTATE_HPP