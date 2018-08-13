#ifndef SCENE_H
#define SCENE_H

#include <cstddef>
#include <map>

#include "Entity.h"

class Scene {
public:
    Scene(void);
    Entity& AddEntity(void);
    Entity& AddEntity(Entity& parent);
    Entity& AddEntity(boost::uuids::uuid id, Entity& parent);
    void RemoveEntity(Entity& entity);
    void MoveEntity(Entity& entity, Entity& target);
    std::optional<std::reference_wrapper<Entity>> GetEntityById(const boost::uuids::uuid id);
private:
    std::map<boost::uuids::uuid, Entity> entities_;
};

#endif