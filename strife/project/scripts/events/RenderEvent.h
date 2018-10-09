#ifndef RENDEREVENT_H
#define RENDEREVENT_H

#include <SDL.h>

#include "Event.h"

class RenderEvent : public Strife::Core::Event {

public:

    using Strife::Core::Event::Event;

    static const unsigned int Priority;

    SDL_Renderer* renderer;

};

#endif // RENDEREVENT_H
