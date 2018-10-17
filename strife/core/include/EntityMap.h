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

			const bool preserveIds_;

		public:
			EntityMap(Scene& scene, bool preserveIds = false);

			Entity getEntity(const boost::uuids::uuid id);
		};
	}  // namespace Core
}  // namespace Strife

#endif  // ENTITYMAP_H
