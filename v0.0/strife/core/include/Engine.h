#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include <string>
#include <typeindex>
#include "Dispatcher.h"
#include "Event.h"
#include "Timer.h"

namespace Strife {
	namespace Core {
        class Scene;

		class Engine {
			
		public:
		
			class TickEvent : public Event {
			
			public:
			
				static const unsigned int Priority;
				
				const Timer::Time time;
				
				TickEvent(const Timer::Time time);
				
			};

		private:

			class Scenes {
			public:
				Scene* active;

				Scenes(Engine& engine);

				void load(const std::string identifier, const std::string path);
				void unload(const std::string identifier);
				void swap(const std::string identifier);

			private:
				Engine& engine_;
				std::map<std::string, Scene> scenes_;
			};

		public:
			static Engine& Instance();

			Scenes scenes;
			Dispatcher dispatcher;
			Timer timer;

			virtual ~Engine() = default;
			
			virtual void loop();

		protected:
			static Engine* instance_;

			Engine();

			virtual void initialize(Scene& scene);
		};

	}  // namespace Core
}  // namespace Strife

#endif
