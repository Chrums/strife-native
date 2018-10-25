#ifndef SCENE_H
#define SCENE_H

#include <functional>
#include <map>
#include <set>
#include <vector>
#include <typeindex>
#include <boost/uuid/uuid.hpp>
#include "Component.h"
#include "Context.h"
#include "Data.h"
#include "Entity.h"
#include "Event.h"
#include "Storage.h"
#include "System.h"

namespace Strife {
	namespace Core {

		class Component;

		class Scene {
			
		public:
            
            class EntityAdded : public Event {
        	public:
        		using Event::Event;
				static const unsigned int Priority;
        	};
            
        	class EntityRemoved : public Event {
        	public:
        		using Event::Event;
				static const unsigned int Priority;
        	};
        
        private:

            class Entities {

			public:
            	
				Entities(Scene& scene, Dispatcher& dispatcher);

                const Entity add();
                void remove(const Entity& entity);
                const Entity get(const boost::uuids::uuid id, Context& context);

            private:
                Scene& scene_;
				Dispatcher& dispatcher_;
			};

			class Components {

			public:
				Components(Scene& scene);
				~Components();

				const Data serialize() const;
                void deserialize(Context context);

				Component* const add(const std::type_index type, const Entity& entity);
				Component* const add(const std::type_index type, const boost::uuids::uuid id, const Entity& entity);
				void remove(const std::type_index type, const Entity& entity);
				void remove(const Entity& entity);
				IStorage* const get(const std::type_index type) const;
				Component* const get(const std::type_index type, const Entity& entity) const;
                const std::map<const std::type_index, IStorage* const>& get() const;

				template <class C>
				Storage<C>& initialize() {
					Component::AssertBase<C>();
					std::type_index type = std::type_index(typeid(C));
					Storage<C>* const storage = new Storage<C>(scene_);
					components_.insert({type, storage});
					identifierToType_.insert({C::Identifier, type});
					typeToIdentifier_.insert({type, C::Identifier});
					return *storage;
				}

				template <class C, class S>
				S& initialize() {
					Component::AssertBase<C>();
					IStorage::AssertBase<S>();
					std::type_index type = std::type_index(typeid(C));
					S* const storage = new S(scene_);
					components_.insert({type, storage});
					identifierToType_.insert({C::Identifier, type});
					typeToIdentifier_.insert({type, C::Identifier});
					return *storage;
				}

				template <class C>
				C* const add(const Entity& entity) {
					std::type_index type(typeid(C));
					Component* const component = add(type, entity);
					return static_cast<C* const>(component);
				}

				template <class C>
				C* const add(const boost::uuids::uuid id, const Entity& entity) {
					std::type_index type(typeid(C));
					Component* const component = add(type, id, entity);
					return static_cast<C* const>(component);
				}

				template <class C>
				void remove(const Entity& entity) {
					std::type_index type(typeid(C));
					remove(type, entity);
				}

				template <class C>
				IStorage* const get() const {
					std::type_index type(typeid(C));
					return components_.at(type);
				}

				template <class C>
				C* const get(const Entity& entity) {
					std::type_index type(typeid(C));
					Component* const component = get(type, entity);
					return static_cast<C* const>(component);
				}

                std::string identifier(std::type_index type);
                std::type_index type(std::string identifier);

			private:
				Scene& scene_;
				std::map<const std::type_index, IStorage* const> components_;
				std::map<std::string, std::type_index> identifierToType_;
				std::map<std::type_index, std::string> typeToIdentifier_;
			};

			class Systems {

			public:
				Systems(Scene& scene, Dispatcher& dispatcher);
				~Systems();

				template <class C>
				System<C>& initialize(Storage<C>& storage) {
					Component::AssertBase<C>();
					std::type_index type(typeid(C));
					System<C>* const system = new System<C>(scene_, dispatcher_, storage);
					systems_.insert({type, system});
					return *system;
				}

				template <class S>
				S& initialize() {
					ISystem::AssertBase<S>();
					std::type_index type(typeid(S));
					S* const system = new S(scene_, dispatcher_);
					systems_.insert({type, system});
					return *system;
				}

				template <class C>
				C* const get() const {
					std::type_index type(typeid(C));
					return static_cast<C*>(systems_.at(type));
				}

			private:
				Scene& scene_;
				Dispatcher& dispatcher_;
				std::map<std::type_index, ISystem* const> systems_;
			};
        	
        public:
        	
			Dispatcher dispatcher;
            Entities entities;
			Components components;
			Systems systems;

			Scene();
			~Scene() = default;

			template <class C>
			void initialize() {
				Storage<C>& storage = components.initialize<C>();
				System<C>& system = systems.initialize<C>(storage);
			}

			const Data serialize() const;
            void deserialize(Data data);
            
		};

	}  // namespace Core
}  // namespace Strife

#endif
