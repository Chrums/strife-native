#ifndef ENTITY_H
#define ENTITY_H

#include <optional>
#include <set>
#include <vector>

#include "Unique.h"

class Scene;

class Entity : public Unique {
public:
    Entity(const Entity& entity);
    Entity(Scene* scene);
    Entity(const boost::uuids::uuid id, Scene* scene);
    std::optional<std::reference_wrapper<Entity>> GetParent(void);
    void SetParent(Entity& entity);
    std::vector<std::optional<std::reference_wrapper<Entity>>> GetChildren(void);
    void AddChild(Entity& entity);
    void RemoveChild(Entity& entity);
private:
    Scene* scene_;
    std::optional<boost::uuids::uuid> parentId_;
    std::set<boost::uuids::uuid> childrenIds_;
};

#endif