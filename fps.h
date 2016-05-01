//
// Created by Francesco Laurita on 4/28/16.
//

#ifndef SDL_SNAKE_FPS_H
#define SDL_SNAKE_FPS_H

#include <SDL2/SDL.h>

namespace snake{
    class Fps {
    public:
        Fps(int fps);
        void update();
        void apply();
        float averageFps();

    private:
        int m_fps;
        Uint32 m_starting_timer;
        Uint32 m_ticks_per_frame;
        Uint32 m_timer_started_at;
        size_t m_cycle;
    };
}

#endif //SDL_SNAKE_FPS_H
