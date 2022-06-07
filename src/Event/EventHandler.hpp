#pragma once

#include <map>
#include <string>
#include "SDL.h"
#include "IEventListener.hpp"

using namespace std;

namespace Event
{
    class EventHandler
    {
    private:
        map<string, IEventListener> listeners;
    public:
        EventHandler();
        ~EventHandler();

        void subscribe(string eventType, IEventListener event);
        void unsubscribe(string eventType);
        void notify(string eventType, SDL_Event e);
        void load();
    };
}