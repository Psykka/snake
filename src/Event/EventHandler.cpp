#include "EventHandler.hpp"
#include "Listeners/Keyboard.hpp"

using namespace Event;

void EventHandler::subscribe(string eventType, IEventListener event)
{
    // listeners.insert(pair<string, IEventListener>(eventType, e));
    listeners[eventType] = event;
}

void EventHandler::unsubscribe(string eventType)
{
    listeners.erase(eventType);
}

void EventHandler::notify(string eventType, SDL_Event e)
{
    listeners[eventType].update(e);
}

void EventHandler::load()
{
    Keyboard keyboard;
    
    subscribe("keyboard", keyboard);
}