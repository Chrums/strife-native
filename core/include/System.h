#ifndef System_H
#define System_H

#include <map>

#include <boost/uuid/uuid.hpp>

#include "Component.h"
#include "Entity.h"

class Scene;

class ISystem {
    
public:
    
    ISystem(Scene* scene) :
        scene_(scene) {};
    
    virtual void Register() = 0;

    virtual Component* Add(Entity* entity) = 0;
    virtual void Remove(Entity* entity) = 0;
    virtual Component* At(Entity* entity) = 0;
    
protected:

    Scene* scene_;
    
};

template <typename T>
class System : public ISystem {
    
public:

    System(Scene* scene) :
        ISystem(scene) {};
    
    void Register(void) {
        //scene_.update += std::bind(&System::Update, this);
        //scene_.render += std::bind(&System::Render, this);
    };
    
    void Update(void) {
        
    };
    
    void Render(void) {
        
    };
    
    T* Add(Entity* entity) {
        return &items_.emplace(entity->id, entity).first->second;
    };
    
    void Remove(Entity* entity) {
        items_.erase(entity->id);
    };
    
    T* At(Entity* entity) {
        return &items_.at(entity->id);
    };
    
private:
    
    std::map<boost::uuids::uuid, T> items_;
    
};

#endif