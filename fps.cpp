//
// Created by Francesco Laurita on 4/28/16.
//
#include "headers.h"

namespace snake {
    Fps::Fps(int fps) {
        m_fps = fps;
        m_cycle = 0;
        m_timer_started_at = SDL_GetTicks();
        m_ticks_per_frame = 1000 / m_fps;
        m_starting_timer = 0;

    }

    void Fps::apply() {
        Uint32 now = SDL_GetTicks();
        if (m_ticks_per_frame > (now - m_starting_timer)){
            SDL_Delay(m_ticks_per_frame - (now - m_starting_timer));
        }
    }

    void Fps::update() {
        m_starting_timer = SDL_GetTicks();
        m_cycle++;
    }

    float Fps::averageFps() {

        Uint32 time = SDL_GetTicks() - m_timer_started_at;
        float avg_fps = m_cycle / ( time / 1000.f );
        if (avg_fps > 2000000){
            avg_fps = 0;
        }
        return avg_fps;
    }

}