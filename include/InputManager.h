#pragma once
#include <SDL.h>

enum class Direction
{
    NONE,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class InputManager
{
public:
    Direction handleInput(bool &running);
};