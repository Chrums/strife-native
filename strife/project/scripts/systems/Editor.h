#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include "ISystem.h"
#include "Dispatcher.h"
#include "forms/MainWindow.h"

class Scene;

class Editor : public Strife::Core::ISystem {

public:
    Editor(Strife::Core::Scene& scene, Strife::Core::Dispatcher& dispatcher);

    virtual void initialize();

    ~Editor();

private:
    MainWindow entityList_;
};

#endif  // EDITOR_H
