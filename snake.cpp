//
// Created by Francesco Laurita on 4/28/16.
//

#include <iostream>
#include <random>
#include "headers.h"

namespace snake {
    Snake::Snake(int xPos,
                 int yPos,
                 float initialSpeed,
                 int windowW,
                 int windowH,
                 int wOffset
    ) {

        wH = windowH;
        wW = windowW;


        resetSpeed = initialSpeed;
        initialLocation = Location {xPos, yPos};
        windowOffset = wOffset;

        reset();

    }
    Snake::~Snake() { }

    void Snake::setDirection(enum Direction dir) {
        // Check for illegal move. Just ignore it
        if (paused || gameOver)
            return;

        if (headDirection == dir)
            return;

        if (headDirection == Direction::UP && dir == Direction::DOWN)
            return;

        if (headDirection == Direction::DOWN && dir == Direction::UP)
            return;

        if (headDirection == Direction::LEFT && dir == Direction::RIGHT)
            return;

        if (headDirection == Direction::RIGHT && dir == Direction::LEFT)
            return;


        headDirection = dir;
    }

    void Snake::render(SDL_Renderer *target) {

        SDL_SetRenderDrawColor(target, 47, 76, 10, 255);
        SDL_Rect r;
        for (std::list<Location>::const_iterator it = locations.begin(), end = locations.end(); it != end; ++it) {
            r.w = 10;
            r.h = 10;
            r.x = (*it).x;
            r.y = (*it).y;
            SDL_RenderFillRect(target, &r);

        }
        r.x = foodLocation.x;
        r.y = foodLocation.y;
        SDL_RenderFillRect(target, &r);
        updatePosition();
    }

    void Snake::updatePosition() {
        if (paused || gameOver)
            return;
        Uint32 now = SDL_GetTicks();
        float delta = now - previousTime;
        if (delta < (1000 / speed))
            return;
        previousTime = SDL_GetTicks();

        int steps = 10;
        Location next = locations.front();
        switch (headDirection){
            case Direction::UP:
                next.y -= steps;
                break;
            case Direction::DOWN:
                next.y += steps;
                break;
            case Direction::RIGHT:
                next.x += steps;
                break;
            case Direction::LEFT:
                next.x -= steps;
                break;

        }
        locations.push_front(next);
        if (next.x == foodLocation.x && next.y == foodLocation.y){
            score += std::ceil(1 * speed);
            needFood = true;
            speed += 0.2;
        } else {
            locations.pop_back();
        }

        if (next.x <= 0 || next.x >= wW + 10){
            gameOver = true;
        }

        if (next.y >= wH + windowOffset - 10 || next.y - windowOffset + 10 <= 0){
            gameOver = true;
        }

        std::list<Location>::const_iterator it = locations.begin();
        it++;
        for (; it != locations.end(); ++it) {
            if (next.x == (*it).x && next.y == (*it).y){
                gameOver = true;
                break;
            }
        }


        if (!gameOver)
            setAppleLocation();
    }

    void Snake::setAppleLocation() {
        if (!needFood)
            return;
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 eng(rd()); // seed the generator
        std::uniform_int_distribution<> distribution_x(10, wW - 10 ); // define the range
        std::uniform_int_distribution<> distribution_y(windowOffset, wH - 10 ); // define the range

        int x = distribution_x(eng);
        if (x % 10 != 0)
            x -= (x % 10);

        int y = distribution_y(eng);
        if (y % 10 != 0)
            y -= (y % 10);

        foodLocation.x = x;
        foodLocation.y = y;
        needFood = false;

    }

    void Snake::pauseToggle() {
        paused ^= true;
    }

    bool Snake::isGameOver() {
        return gameOver;
    }

    void Snake::reset() {
        speed = resetSpeed;
        needFood = true;
        paused = false;
        gameOver = false;
        score = 0;

        previousTime = SDL_GetTicks();
        headDirection = Direction::DOWN;

        locations = std::list<Location>();
        locations.push_front(initialLocation);
        setAppleLocation();

    }

    bool Snake::isPaused() {
        return paused;
    }

    int Snake::getScore() {
        return score;
    }


}