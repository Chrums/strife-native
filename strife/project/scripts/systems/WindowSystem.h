#ifndef ENTITY_LIST_H
#define ENTITY_LIST_H

#include <string>
#include <unordered_map>
#include <SDL.h>
#include <SDL_image.h>
#include <QApplication>

#include "Data.h"
#include "System.h"
#include "Dispatcher.h"
#include "EntityMap.h"
#include "Event.h"
#include "events/RenderEvent.h"

#include "forms/MainWindow.h"

class Scene;

class WindowSystem : public Strife::Core::ISystem {

public:
    WindowSystem(Strife::Core::Scene& scene, Strife::Core::Dispatcher& dispatcher);

    virtual void initialize();

    ~WindowSystem();

private:
    QApplication* application_;

    int argc_;
    char argv_[10][10];

    void pumpQT(Strife::Core::Event* event, std::type_index eventType);
};

#endif
