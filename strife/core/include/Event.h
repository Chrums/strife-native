#ifndef EVENT_H
#define EVENT_H

#include "Entity.h"

namespace Strife {
    namespace Core {

        class Event {

        public:

            static const unsigned int Synchronous;

            const Entity& entity;

            Event(const Entity& entity);

            virtual ~Event() = default;

        };

    }
}

#endif
