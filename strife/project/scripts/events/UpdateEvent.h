#ifndef UPDATEEVENT_H
#define UPDATEEVENT_H

#include <SDL.h>

#include "Event.h"

class UpdateEvent : public Strife::Core::Event {

public:

	static const unsigned int Priority;

	UpdateEvent(Uint32 dt)
	    : dt(dt) {}

	Uint32 dt;

};

#endif  // RENDEREVENT_H
