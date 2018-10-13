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

EntityList::EntityList(Strife::Core::Scene& scene, Strife::Core::Dispatcher& dispatcher)
    : ISystem(scene)
    , active_(true) {

    dispatcher.initialize<RenderEvent>();
    dispatcher.on<RenderEvent>([this](const RenderEvent& event) { render(event); });
}

EntityList::~EntityList() {}

void EntityList::render(const RenderEvent& event) {
    size_t numEntities = scene_.entities.get().size();
    if (ImGui::Begin("Entities", &active_, ImGuiWindowFlags_MenuBar)) {
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
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Entities: %d", numEntities);
        if (ImGui::BeginPopupContextItem("item context menu")) {
            ImGui::Selectable("Add new entity");
            ImGui::EndPopup();
        }
        ImGui::BeginChild("Scrolling");
        for (auto entity : scene_.entities.get()) {
            string entityId = boost::lexical_cast<string>(entity.id);
            if (ImGui::TreeNode(entityId.c_str())) {
                for (auto& [type, storage] : scene_.components.get()) {
                    auto component = storage->get(entity);
                    if (component != nullptr) {
                        if (ImGui::TreeNode(scene_.components.identifier(type).c_str())) {
                            string componentData = component->serialize().dump();
                            ImGui::Text("%s", componentData.c_str());
                            ImGui::TreePop();
                            ImGui::Separator();
                        }
                    }
                }
                ImGui::TreePop();
                ImGui::Separator();
            }
        }
        ImGui::EndChild();
    }
    ImGui::End();
}
