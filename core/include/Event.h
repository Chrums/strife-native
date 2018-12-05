#ifndef EVENT_H
#define EVENT_H

#include <optional>
#include "Entity.h"
#include "Message.h"

namespace Strife {
    namespace Core {
        
        class Event : public Message {
            
        public:
        
            template <class E>
            static void AssertBase();
            
            const std::optional<Entity> target;
            
            Event();
            Event(const Entity target);
            virtual ~Event() = default;
            
        };

		template <class E>
		void Event::AssertBase() {
			static_assert(std::is_base_of<Event, E>::value, "Type not derived from Event");
		};
        
    }
}

#endif