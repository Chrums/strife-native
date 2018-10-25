#ifndef COMPONENT_H
#define COMPONENT_H

#include <boost/uuid/uuid.hpp>
#include "Context.h"
#include "Data.h"
#include "Entity.h"
#include "Unique.h"

namespace Strife {
	namespace Core {

		class Scene;

		class Component : public Unique {
		public:
			template <class C>
			static void AssertBase();

			const Entity entity;
			Scene& scene;

			Component(const Entity& entity);
			Component(const boost::uuids::uuid id, const Entity& entity);
			virtual ~Component() = default;

			virtual const Data serialize() const;
            virtual void deserialize(Context context);
		};

		template <class C>
		void Component::AssertBase() {
            static_assert(std::is_base_of<Component, C>::value, "Type not derived from Component");
		}

	}  // namespace Core
}  // namespace Strife

#endif
