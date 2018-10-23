#ifndef ENTITY_H
#define ENTITY_H

#include <typeindex>
#include <functional>
#include <boost/uuid/uuid.hpp>
#include "Unique.h"

namespace Strife {
    namespace Core {

	    class Scene;
		class Component;

		class Entity : public Unique {

			class Components {

			public:
				Components(Entity& entity);

				Component* const add(const std::type_index type);
				Component* const add(const std::type_index type, const boost::uuids::uuid id);
				void remove(const std::type_index type);
				Component* const get(const std::type_index type) const;

				template <class T>
				T* const add() {
					const std::type_index type(typeid(T));
					Component* const component = add(type);
					return static_cast<T* const>(component);
				};

				template <class T>
				T* const add(const boost::uuids::uuid id) {
					const std::type_index type(typeid(T));
					Component* const component = add(type, id);
					return static_cast<T* const>(component);
				};

				template <class T>
				void remove() {
					const std::type_index type(typeid(T));
					remove(type);
				};

				template <class T>
				T* const get() const {
					const std::type_index type(typeid(T));
					Component* const component = get(type);
					return static_cast<T* const>(component);
				};

			private:
				Entity& entity_;
			};

		public:
			Scene* scene;
			Components components;

			Entity(const Entity& entity);
			Entity(Scene& scene);
			Entity(const boost::uuids::uuid id, Scene& scene);

			bool operator==(const Entity& rhs) const;
			bool operator!=(const Entity& rhs) const;

			void destroy();
		};

	}  // namespace Core
}  // namespace Strife

namespace std {
    template <>
    struct hash<Strife::Core::Entity> {
		size_t operator()(const Strife::Core::Entity& entity) const {
			return hash<Strife::Core::Unique>{}(entity);
		}
	};
}  // namespace std

#endif
