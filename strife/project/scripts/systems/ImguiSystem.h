#ifndef IMGUI_H
#define IMGUI_H

#include "ISystem.h"
#include "Dispatcher.h"

class Scene;
class SDL_Window;
class SDL_Texture;
class SDL_Renderer;

class ImguiSystem : public Strife::Core::ISystem {
public:
    ImguiSystem(Strife::Core::Scene& scene, Strife::Core::Dispatcher& dispatcher);

    virtual void initialize();

    void handleMouse(SDL_Window* window);
    void init(SDL_Renderer* renderer);
    void finishRender();
    void beginRender(/*SDL_Texture* texture*/);

    ~ImguiSystem();

private:
    bool mousePressed_[3];
    Strife::Core::Dispatcher& dispatcher_;
};

#endif // IMGUI_H
