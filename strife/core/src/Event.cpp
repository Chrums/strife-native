#include "Event.h"

using namespace Strife::Core;
using namespace std;

const unsigned int Event::Synchronous = 0;

Event::Event(const optional<Entity> entity)
    : entity(entity){};
