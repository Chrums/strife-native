#ifndef IMGUI_H
#define IMGUI_H

#include "ISystem.h"
#include "Dispatcher.h"

class Scene;
struct SDL_Window;
struct SDL_Texture;
struct SDL_Renderer;
class FinishGui;
class BeginGui;

class ImguiSystem : public Strife::Core::ISystem {
public:
	ImguiSystem(Strife::Core::Scene& scene, Strife::Core::Dispatcher& dispatcher);

	void handleMouse(SDL_Window* window);
	void init(SDL_Renderer* renderer);
	void finishRender(const FinishGui& event);
	void beginRender(const BeginGui& event);

	~ImguiSystem();

private:
	bool mousePressed_[3];
	Strife::Core::Dispatcher& dispatcher_;
};

#endif  // IMGUI_H
