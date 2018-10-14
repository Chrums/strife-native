#include "EntityList.h"

#include <SDL.h>
#include <imgui.h>
#include <boost/lexical_cast.hpp>
#include "utility/imgui_impl_sdl.h"
#include "utility/imgui_sdl.h"
#include "Scene.h"
#include "Dispatcher.h"
#include "Data.h"
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

Data renderData(Data item, string key = "") {
    switch (item.type()) {
        case Data::value_t::object: {
            for (auto pair : item.items()) {
                item[pair.key()] = renderData(pair.value(), pair.key());
            }
            break;
        }
        case Data::value_t::number_integer: {
            int value = static_cast<int>(item.get<Data::number_integer_t>());
            if (ImGui::InputInt(key.c_str(), &value)) {
                return Data(value);
            }
            break;
        }
        case Data::value_t::number_unsigned: {
            int value = static_cast<int>(item.get<Data::number_unsigned_t>());
            if (ImGui::InputInt(key.c_str(), &value)) {
                if (value >= 0) {
                    return Data(value);
                }
            }
            break;
        }
        case Data::value_t::number_float: {
            double* value = item.get<Data::number_float_t*>();
            if (ImGui::InputDouble(key.c_str(), value)) {
                //*item.value().get<Data::number_integer_t*>() = value;
            }
            break;
        }
        case Data::value_t::string: {

            string value = item.get<Data::string_t>();

            std::string clipText = (ImGui::GetClipboardText() != nullptr) ? ImGui::GetClipboardText() : "";
            size_t clipSize = clipText.length();
            size_t size = value.length() + clipSize + 5;
            char* newText = static_cast<char*>(malloc(sizeof(char) * size));
            strncpy(newText, value.c_str(), size);

            if (ImGui::InputText(key.c_str(), newText, size)) {
                item = Data(string(newText));
            }
            delete newText;
            break;
        }
        case Data::value_t::boolean:
        case Data::value_t::null:
        case Data::value_t::array: {
            size_t index = 0;
            for (auto arrayItem : item) {
                stringstream indexString;
                indexString << index;
                item[index] = renderData(arrayItem, indexString.str());
                index++;
            }
            break;
        }
        default:
            ImGui::Text("%s", key.c_str());
            ImGui::Text("%s", item.dump().c_str());
    }
    return item;
}

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
                            Data componentData = component->serialize();
                            Data modifiedData = renderData(componentData);
                            EntityMap emap(scene_);  // TODO: Need to add option to avoid reassigning uuids
                            component->deserialize(modifiedData, emap);
                            ImGui::TreePop();
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
