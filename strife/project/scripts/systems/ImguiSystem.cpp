#include "ImguiSystem.h"

#include <SDL.h>
#include <imgui.h>
#include "utility/imgui_impl_sdl.h"
#include "utility/imgui_sdl.h"
#include "Scene.h"
#include "Dispatcher.h"
#include "events/BeginGui.h"
#include "events/FinishGui.h"

ImguiSystem::ImguiSystem(Strife::Core::Scene &scene, Strife::Core::Dispatcher &dispatcher)
    : ISystem(scene)
    , dispatcher_(dispatcher) {
	mousePressed_[0] = false;
	mousePressed_[1] = false;
	mousePressed_[2] = false;

	dispatcher.on<BeginGui>([this](const BeginGui& event) { beginRender(event); });
	dispatcher.on<FinishGui>([this](const FinishGui& event) { finishRender(event); });
}

void ImguiSystem::handleMouse(SDL_Window *window) {
	ImGuiIO &io = ImGui::GetIO();

	// Set OS mouse position if requested (rarely used, only when ImGuiConfigFlags_NavEnableSetMousePos is enabled by user)
	if (io.WantSetMousePos) {
		SDL_WarpMouseInWindow(window, static_cast<int>(io.MousePos.x), static_cast<int>(io.MousePos.y));
	} else {
		io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
	}

	int mx, my;
	Uint32 mouse_buttons = SDL_GetMouseState(&mx, &my);
	io.MouseDown[0] = mousePressed_[0] || (mouse_buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) !=
	                                          0;  // If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
	io.MouseDown[1] = mousePressed_[1] || (mouse_buttons & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0;
	io.MouseDown[2] = mousePressed_[2] || (mouse_buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0;
	mousePressed_[0] = mousePressed_[1] = mousePressed_[2] = false;

	if (SDL_GetWindowFlags(window) & SDL_WINDOW_INPUT_FOCUS) {
		io.MousePos = ImVec2(static_cast<float>(mx), static_cast<float>(my));
	}
}

void ImguiSystem::init(SDL_Renderer *renderer) {
	ImGui::CreateContext();
	ImGuiSDL::Initialize(renderer, 640, 480);
	ImGui::StyleColorsDark();
}

void ImguiSystem::finishRender(const FinishGui& event) {
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
}

void ImguiSystem::beginRender(const BeginGui& event) {

	ImGui::NewFrame();
	ImGui::ShowDemoWindow();

	/*ImGui::Begin("Image");
	ImGui::Image(texture, ImVec2(100, 100));
	ImGui::End();*/
}

ImguiSystem::~ImguiSystem() {}
