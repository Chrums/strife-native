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
    
    virtual void initialize() = 0;

    virtual Component* add(Entity* entity) = 0;
    virtual void remove(Entity* entity) = 0;
    virtual Component* at(Entity* entity) = 0;
    
protected:

    Scene* scene_;
    
};

template <typename T>
class System : public ISystem {
    
public:

    System(Scene* scene) :
        ISystem(scene) {};
    
    void initialize() {
        //scene_.updates += Bind(&System::Update, this);
        //scene_.renders += Bind(&System::Render, this);
    };
    
    void update() {
        
    };
    
    void render() {
        
    };
    
    T* add(Entity* entity) {
        return &items_.emplace(entity->id, entity).first->second;
    };
    
    void remove(Entity* entity) {
        items_.erase(entity->id);
    };
    
    T* at(Entity* entity) {
        return &items_.at(entity->id);
    };
    
private:
    
    std::map<boost::uuids::uuid, T> items_;
    
};

#endif