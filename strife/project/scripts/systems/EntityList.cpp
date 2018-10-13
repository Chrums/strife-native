#include "EntityList.h"

#include <SDL.h>
#include <imgui.h>
#include <boost/lexical_cast.hpp>
#include "utility/imgui_impl_sdl.h"
#include "utility/imgui_sdl.h"
#include "Scene.h"
#include "Dispatcher.h"
#include "events/RenderEvent.h"

using namespace Strife::Core;
using namespace std;

EntityList::EntityList(Strife::Core::Scene &scene, Strife::Core::Dispatcher &dispatcher)
    : ISystem(scene)
    , active_(true) {

    dispatcher.initialize<RenderEvent>();
    dispatcher.on<RenderEvent>([this](const RenderEvent &event) { render(event); });
}

void EntityList::initialize() {}

EntityList::~EntityList() {}

void EntityList::render(const RenderEvent &event) {
    // Create a window called "My First Tool", with a menu bar.
    ImGui::Begin("My First Tool", &active_, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */
            }
            if (ImGui::MenuItem("Close", "Ctrl+W")) {
                active_ = false;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    // Display contents in a scrolling region
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
    ImGui::BeginChild("Scrolling");
    for (auto entity : scene_.entities.get()) {
        ImGui::Text(boost::lexical_cast<string>(entity.id).c_str());
    }
    ImGui::EndChild();
    ImGui::End();
}
