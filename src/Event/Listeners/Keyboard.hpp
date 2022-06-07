#pragma once
#include "../IEventListener.hpp"

namespace Event
{
    class Keyboard : public IEventListener
    {
    private:
    public:
        virtual ~Keyboard();

        void update(SDL_Event e) override;
    };
}
