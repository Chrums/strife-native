#ifndef RENDEREVENT_H
#define RENDEREVENT_H

#include <SDL.h>

#include "Event.h"

class RenderEvent : public Strife::Core::Event {

public:

	static const unsigned int Priority;

	RenderEvent(SDL_Renderer* renderer, Uint32 dt)
	    : renderer(renderer)
	    , dt(dt) {}

	RenderEvent(const Strife::Core::Event target, SDL_Renderer* renderer, Uint32 dt)
	    : Event(target)
	    , renderer(renderer)
	    , dt(dt) {}

	SDL_Renderer* renderer;
	Uint32 dt;

};

#endif  // RENDEREVENT_H
