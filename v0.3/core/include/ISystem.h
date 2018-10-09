#ifndef ISYSTEM_H
#define ISYSTEM_H

#include <map>
#include <string>
#include <functional>
#include <vector>
#include <boost/uuid/uuid.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
#include <typeindex>

namespace Strife {
    namespace Core {

        class Scene;
        class Component;

        class ISystem {

        public:

            ISystem(Scene* const scene) :
                scene_(scene) {};

            virtual ~ISystem() = default;

            virtual void initialize() = 0;

        protected:

            Scene* const scene_;

            std::vector<Component*> const getComponents(std::type_index type) const;

            template <class T>
            std::vector<Component*> const getComponents() const {
                const std::type_index type = std::type_index(typeid(T));
                return getComponents(type);
            }

        };
    }
}

#endif
