#include "Event.h"

using namespace Strife::Core;
using namespace std;

Event::Event()
    : target(nullopt) {}
    
Event::Event(const Entity target)
    : target(target) {}