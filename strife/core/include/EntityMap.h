#ifndef ENTITYMAP_H
#define ENTITYMAP_H

#include <map>
#include <boost/uuid/uuid.hpp>

namespace Strife {
    namespace Core {
        class Scene;
        class Entity;

        class EntityMap {

            Scene& scene_;

            std::map<boost::uuids::uuid, Entity> uuidMap;

        public:
            EntityMap(Scene& scene);

            Entity getEntity(const boost::uuids::uuid id);
        };
    }  // namespace Core
}  // namespace Strife

#endif  // ENTITYMAP_H
