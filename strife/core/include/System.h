#ifndef SYSTEM_H
#define SYSTEM_H

#include <map>
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
#include "Component.h"
#include "Entity.h"

namespace Strife {
    namespace Core {
    
        class Scene;
        
        class ISystem {
            
        public:
        
            ISystem(Scene* const scene) :
                scene_(scene) {};
                
            virtual ~ISystem() = default;
        
            virtual void intialize() const = 0;
            
        protected:
            
            Scene* const scene_;
            
        };
        
        template <class T>
        class System : public ISystem {
            
        public:
        
            System(Scene* const scene) :
                ISystem(scene) {};
            
            void initialize() const {
                
            };
            
        };
    
    }
}

#endif