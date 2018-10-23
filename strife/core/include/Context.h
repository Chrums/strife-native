#ifndef CONTEXT_H
#define CONTEXT_H

#include "Data.h"

using namespace Strife {
    using namespace Core {

        class Scene;

        class Context {
        				
        public:
        
        	const Data data;
        
        	Context(Scene& scene);
        	Context& bind(const Data data);
        	
        private:
        
        	Context(Scene& scene, const Data data);
        	
        	Scene& scene_;
        	std::map<boost::uuids::uuid, boost::uuids::uuid> context_;
        	
        };

    }
}

#endif