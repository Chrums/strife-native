#ifndef FINISHGUI_H
#define FINISHGUI_H

#include "Event.h"


class FinishGui : public Strife::Core::Event
{
public:

	static const unsigned int Priority;

	using Strife::Core::Event::Event;
};

#endif // ONGUI_H
