#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include <string>
#include <typeindex>
#include "Dispatcher.h"

namespace Strife {
	namespace Core {
        class Scene;

		class Engine {

			class Scenes : private std::map<std::string, Scene> {
			public:
				Scene* active;

				Scenes(Engine& engine);

				void load(const std::string identifier, const std::string path);
				void unload(const std::string identifier);
				void swap(const std::string identifier);

			private:
				Engine& engine_;
			};

		public:
			static Engine* Instance();

			Scenes scenes;
			Dispatcher dispatcher;

			virtual ~Engine() = default;

		protected:
			static Engine* instance_;

			Engine();

			virtual void initialize(Scene& scene);
		};

	}  // namespace Core
}  // namespace Strife

#endif
