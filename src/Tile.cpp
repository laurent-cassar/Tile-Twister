#include "Tile.hpp"

Tile::Tile() : value_(0), row_(0), col_(0) {}

Tile::Tile(int value, int row, int col) 
    : value_(value), row_(row), col_(col) {}

bool Tile::canMergeWith(const Tile& other) const {
    return !isEmpty() && value_ == other.value_;
}

void Tile::merge(const Tile& other) {
    if (canMergeWith(other)) {
        value_ *= 2;
    }
}