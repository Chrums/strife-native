#ifndef COMPONENT_H
#define COMPONENT_H

#include <boost/uuid/uuid.hpp>
#include "Data.h"
#include "Entity.h"
#include "Scene.h"
#include "Unique.h"

namespace Strife {
    namespace Core {

        class Component : public Unique {

        public:

            const Entity entity;
            Scene& scene;

            virtual const Data serialize() const;
            virtual void deserialize(const Data data);

        protected:

            Component(const Entity& entity);
            Component(const boost::uuids::uuid id, const Entity& entity);

        };

    }
}

#endif
