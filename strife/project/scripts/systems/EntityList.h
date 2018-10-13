#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include "ISystem.h"
#include "Dispatcher.h"
#include "events/RenderEvent.h"
#include <SDL.h>

class Scene;

class EntityList : public Strife::Core::ISystem {
public:
    EntityList(Strife::Core::Scene& scene, Strife::Core::Dispatcher& dispatcher);

    virtual void initialize();

    ~EntityList();

    void render(const RenderEvent& event);

private:
    bool active_;
};

#endif
