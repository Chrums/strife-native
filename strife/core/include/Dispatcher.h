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
#include "Messenger.h"

namespace Strife {
	namespace Core {

		class Dispatcher {
		public:
		
			static const unsigned int Synchronous;
		
			void emit(const std::type_index type, const unsigned int priority, Event* const event);
			
			void dispatch();
			void dispatch(const std::type_index type);
			void dispatch(const std::type_index type, Event* const event);
			
			template <class E>
            void initialize() {
			    Event::AssertBase<E>();
                const std::type_index type = std::type_index(typeid(E));
                events_.try_emplace(type);
                priorities_[E::Priority].insert(type);
            }
			
			template <class E>
			void on(Messenger::Callback<E> callback) {
			    Event::AssertBase<E>();
				const std::type_index type = std::type_index(typeid(E));
				messenger.on<E>(callback);
			};

			template <class E, typename... Args>
			void emit(Args... args) {
			    Event::AssertBase<E>();
                const std::type_index type = std::type_index(typeid(E));
				E* const event = new E(std::forward<Args>(args)...);
				const unsigned int priority = E::Priority;
				emit(type, priority, event);
			}

		private:
		
			Messenger messenger;
			std::map<const std::type_index, std::queue<Event*>> events_;
			std::map<const unsigned int, std::set<std::type_index>> priorities_;
			
		};

	}  // namespace Core
}  // namespace Strife

#endif
