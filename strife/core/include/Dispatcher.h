#ifndef EVENTS_H
#define EVENTS_H

#include <functional>
#include <map>
#include <set>
#include <typeindex>
#include <queue>
#include <vector>
#include "Entity.h"
#include "Event.h"

namespace Strife {
	namespace Core {

		typedef std::function<void(Event*, std::type_index)> Callback;

		class Dispatcher {

		public:
			template <class T>
			void initialize() {
				const std::type_index type = std::type_index(typeid(T));
				events_[type];
				std::set<std::type_index>& types = priorities_[T::Priority];
				types.insert(type);
			}

			template <class T>
			void on(Callback callback) {
				const std::type_index type = std::type_index(typeid(T));
				auto callbacks = callbacks_.find(type);
				if (callbacks == callbacks_.end()) {
					std::vector<Callback> callbackVector;
					callbackVector.push_back(callback);
					callbacks_.insert({type, callbackVector});
				} else {
					callbacks->second.push_back(callback);
				}
			};

			void trigger(const std::type_index type, Event* event, const unsigned int priority) {
				if (priority == Event::Synchronous) {
					dispatch(type, event);
				} else {
					auto events = events_.find(type);
					if (events == events_.end()) {
						std::queue<Event*> eventQueue;
						eventQueue.push(event);
						events_.insert({type, eventQueue});
					} else {
						events->second.push(event);
					}
				}
			}

			template <class T>
			void trigger(const std::optional<Entity> entity) {
				const std::type_index type = std::type_index(typeid(T));
				T* const event = new T(entity);
				const unsigned int priority = T::Priority;
				trigger(type, event, priority);
			};

			template <class T>
			void trigger(const std::optional<Entity> entity, std::function<void(T&)> initializer) {
				const std::type_index type = std::type_index(typeid(T));
				T* const event = new T(entity);
				const unsigned int priority = T::Priority;
				initializer(*event);
				trigger(type, event, priority);
			};

			template <class T, typename... ArgTypes>
			void triggerArg(ArgTypes... args) {
				const std::type_index type = std::type_index(typeid(T));
				T* const event = new T(std::forward<ArgTypes>(args)...);
				const unsigned int priority = T::Priority;
				trigger(type, event, priority);
			}

			template <class T>
			void trigger(std::function<void(T&)> initializer) {
				trigger<T>(std::nullopt, initializer);
			};

			template <class T>
			void trigger() {
				trigger<T>(std::nullopt);
			};

			void dispatch(const std::type_index type, Event* event) {
				auto callbacks = callbacks_.find(type);
				if (callbacks != callbacks_.end()) {
					for (auto callback : callbacks->second) {
						callback(event, type);
					}
				}
				delete event;
			}

			void dispatch(const std::type_index type) {
				auto events = events_.find(type);
				if (events == events_.end()) {
					return;
				}
				size_t num_events = events->second.size();
				for (size_t i = 0; i < num_events; i++) {
					Event* event = events->second.front();
					events->second.pop();
					dispatch(type, event);
				}
			}

			void dispatch() {
				for (auto priority : priorities_) {
					for (auto type : priority.second) {
						dispatch(type);
					}
				}
			}

		private:
			std::map<const std::type_index, std::queue<Event*>> events_;
			std::map<const unsigned int, std::set<std::type_index>> priorities_;
			std::map<const std::type_index, std::vector<Callback>> callbacks_;
		};

	}  // namespace Core
}  // namespace Strife

#endif
