#include "Event.h"

using namespace Strife::Core;
using namespace std;

Event::Event()
    : entity(nullopt) {}

Event::Event(const Entity entity)
    : entity(entity) {}
