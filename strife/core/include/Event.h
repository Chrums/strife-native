#ifndef EVENT_H
#define EVENT_H

#include "Entity.h"
#include <optional>

namespace Strife {
	namespace Core {

		class Event {

		public:
			static const unsigned int Synchronous;

			const std::optional<Entity> entity;

			Event(const std::optional<Entity> entity);

			virtual ~Event() = default;
		};

	}  // namespace Core
}  // namespace Strife

#endif
