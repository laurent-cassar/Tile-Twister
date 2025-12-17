#include "GameState.hpp"
#include <fstream>
#include <iostream>

GameState::GameState() : state_(State::PLAYING), score_(0), bestScore_(0) {
    loadBestScore();
}

void GameState::reset() {
    state_ = State::PLAYING;
    score_ = 0;
}

void GameState::updateBestScore() {
    if (score_ > bestScore_) {
        bestScore_ = score_;
        saveBestScore();
    }
}

void GameState::loadBestScore() {
    std::ifstream file("best_score.txt");
    if (file.is_open()) {
        file >> bestScore_;
        file.close();
    } else {
        bestScore_ = 0;
    }
}

void GameState::saveBestScore() const {
    std::ofstream file("best_score.txt");
    if (file.is_open()) {
        file << bestScore_;
        file.close();
    }
}

bool GameState::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    file << static_cast<int>(state_) << "\n";
    file << score_ << "\n";
    file << bestScore_ << "\n";
    
    file.close();
    return true;
}

bool GameState::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    int stateInt;
    file >> stateInt;
    state_ = static_cast<State>(stateInt);
    file >> score_;
    file >> bestScore_;
    
    file.close();
    return true;
}