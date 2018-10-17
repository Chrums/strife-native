#ifndef ONGUI_H
#define ONGUI_H

#include "Event.h"


class OnGui : public Strife::Core::Event
{
public:

	static const unsigned int Priority;

	using Strife::Core::Event::Event;
};

#endif // ONGUI_H
