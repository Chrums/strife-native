#ifndef STORAGE_H
#define STORAGE_H

#include <functional>
#include <unordered_map>
#include <set>
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Component.h"
#include "Data.h"
#include "Entity.h"
#include "IIterator.h"
#include "IStorage.h"
#include "EntityMap.h"

namespace Strife {
    namespace Core {

        class Scene;

		template <class C>
		class Storage : public IStorage {

            // TODO: Figure out how to use std::hash
            struct EntityHash {
                std::size_t operator()(const Entity& key) const {
                    return std::hash<Entity>{}(key);
                }
            };

			class Iterator : public IIterator<std::pair<const Entity, Component* const>> {

			public:
                Iterator(typename std::unordered_map<Entity, C, EntityHash>::iterator iterator)
				    : iterator_(iterator) {}

				~Iterator() = default;

				void operator++() {
					iterator_++;
				}

				std::pair<const Entity, Component* const> operator*() {
					return {iterator_->first, &iterator_->second};
				}

				bool operator==(const IIterator<std::pair<const Entity, Component* const>>* const iterator) const {
					return iterator_ == static_cast<const Iterator*>(iterator)->iterator_;
				}

			private:
                typename std::unordered_map<Entity, C, EntityHash>::iterator iterator_;
			};

		public:
			Storage(Scene& scene)
			    : IStorage(scene) {}

			const Data serialize() const {
				Data data;
				for (const auto& [ entity, component ] : components_) {
					const std::string entityIdentifier = boost::lexical_cast<std::string>(entity.id);
					const Data componentData = component.serialize();
					data[entityIdentifier] = componentData;
				}
				return data;
			}

            void deserialize(const Data data, EntityMap& entityMap) {
				for (auto& iteratorEntityIdentifierToComponentData : data.items()) {
					const std::string entityIdentifier = iteratorEntityIdentifierToComponentData.key();
					const Data componentData = iteratorEntityIdentifierToComponentData.value();
					const boost::uuids::uuid entityId = boost::lexical_cast<boost::uuids::uuid>(entityIdentifier);
                    const Entity entity = entities_.add(entityId, entityMap);
					C* const component = add(entity);
                    component->deserialize(componentData, entityMap);
				}
			}

			C* const add(const Entity entity) {
                return &components_.emplace(entity, entity).first->second;
			}

			C* const add(const boost::uuids::uuid id, const Entity entity) {
                return &components_.try_emplace(entity, id, entity).first->second;
			}

			void remove(const Entity entity) {
                components_.erase(entity);
            }

            C* const get(const Entity entity) const {
                auto componentIt = components_.find(entity);
                if (componentIt != components_.end()) {
                    return const_cast<C* const>(&componentIt->second);
                }
                return nullptr;
			}

			IStorage::Iterator begin() {
                return IStorage::Iterator(new Iterator(components_.begin()));
			}

			IStorage::Iterator end() {
                return IStorage::Iterator(new Iterator(components_.end()));
			}

        private:
            std::unordered_map<Entity, C, EntityHash> components_;
		};

	}  // namespace Core
}  // namespace Strife

#endif
