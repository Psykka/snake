#pragma once

#include "SDL.h"

namespace Event
{
    class IEventListener
    {
    public:
        virtual ~IEventListener();

        virtual void update(SDL_Event e);
    };
}