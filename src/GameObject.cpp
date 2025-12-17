#include "GameObject.hpp"

GameObject::GameObject(int x, int y, int width, int height) {
    rect_.x = x;
    rect_.y = y;
    rect_.w = width;
    rect_.h = height;
}

void GameObject::setPosition(int x, int y) {
    rect_.x = x;
    rect_.y = y;
}

void GameObject::setSize(int width, int height) {
    rect_.w = width;
    rect_.h = height;
}