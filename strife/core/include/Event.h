#ifndef EVENT_H
#define EVENT_H

#include "Entity.h"
#include "Message.h"
#include <optional>

namespace Strife {
	namespace Core {

		class Event : public Message {

		public:

			template <class E>
			static void AssertBase();

			const std::optional<Entity> entity;

			Event();
			Event(const Entity entity);
			virtual ~Event() = default;
			
		};

		template <class E>
		void Event::AssertBase() {
			static_assert(std::is_base_of<Event, E>::value, "Type not derived from Event");
		};

	}  // namespace Core
}  // namespace Strife

#endif
