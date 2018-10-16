#ifndef COMPONENT_H
#define COMPONENT_H

#include <boost/uuid/uuid.hpp>
#include <MetaStuff/Meta.h>
#include "Data.h"
#include "Entity.h"
#include "Unique.h"
#include "EntityMap.h"
#include "JsonCast.h"

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
            virtual void deserialize(const Data data, EntityMap& entityMap);

        protected:
            template <class C>
            const Data toJson() const;
            template <class C>
            void fromJson(const Data data, EntityMap& entityMap);
        };

        template <class C>
        void Component::AssertBase() {
            static_assert(std::is_base_of<Component, C>::value, "Type not derived from Component");
        }

        template <class C>
        const Data Component::toJson() const {
            return meta::serialize(*static_cast<const C*>(this));
        }

        template <class C>
        void Component::fromJson(const Data data, EntityMap& entityMap) {
            meta::deserialize(*static_cast<C*>(this), data, entityMap);
        }

    }  // namespace Core
}  // namespace Strife

#endif
