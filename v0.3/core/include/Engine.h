#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include <string>
#include <typeindex>
#include "Scene.h"
#include "Dispatcher.h"

namespace Strife {
    namespace Core {

        class Engine {

            class Scenes : std::map<std::string, Scene> {

            public:

                Scenes(Engine* engine) : engine_(engine), active(nullptr) {
                }

                Scene* active;

                void load(const std::string identifier, const std::string path);
                void unload(const std::string identifier);
                void swap(const std::string identifier);

            private:

                Engine* engine_;

            };

            class Components {

            public:

                template <class T>
                void initialize(std::string identifier) {
                    std::type_index type = std::type_index(typeid(T));
                    identifierToType_.insert({ identifier, type });
                    typeToIdentifier_.insert({ type, identifier });
                };

            private:

                std::map<std::string, std::type_index> identifierToType_;
                std::map<std::type_index, std::string> typeToIdentifier_;

            };

        public:

            static Engine* Instance();

            Scenes scenes;
            Dispatcher dispatcher;

            ~Engine();

        protected:

            static Engine* instance_;
            virtual void initialize() {};
            Engine() : scenes(this){}

        };

    }
}

#endif
