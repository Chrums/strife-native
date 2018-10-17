#ifndef BEGINGUI_H
#define BEGINGUI_H

#include "Event.h"

class BeginGui : public Strife::Core::Event
{
public:

	static const unsigned int Priority;

	using Strife::Core::Event::Event;
};

#endif // ONGUI_H
