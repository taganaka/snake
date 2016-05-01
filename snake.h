//
// Created by Francesco Laurita on 4/28/16.
//

#ifndef SDL_SNAKE_SNAKE_H
#define SDL_SNAKE_SNAKE_H
#include <SDL2/SDL.h>
#include <list>

namespace snake {
    enum class Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    class Location{
    public:
        int x;
        int y;
    };

    class Snake{
    public:
        Snake(int xPos,
              int yPos,
              float initialSpeed,
              int windowW,
              int windowH,
              int windowOffset
        );
        ~Snake();
        void setDirection(enum Direction);
        void pauseToggle();
        void render(SDL_Renderer *target);
        bool isGameOver();
        bool isPaused();
        void reset();
        int getScore();

    private:
        float speed;
        float resetSpeed;

        int wW;
        int wH;

        int score;
        int windowOffset;

        bool needFood;
        bool paused;
        bool gameOver;

        Location initialLocation;
        Location foodLocation;
        std::list<Location> locations;
        Direction headDirection;

        Uint32 previousTime;

        void updatePosition();
        void setAppleLocation();

    };
}

#endif //SDL_SNAKE_SNAKE_H
