#include "EntityList.h"

#include <SDL.h>
#include <imgui.h>
#include <boost/lexical_cast.hpp>
#include "utility/imgui_impl_sdl.h"
#include "utility/imgui_sdl.h"
#include "Scene.h"
#include "Dispatcher.h"
#include "Data.h"
#include "events/OnGui.h"
#include "events/SelectEntity.h"

using namespace Strife::Core;
using namespace std;

EntityList::EntityList(Strife::Core::Scene& scene, Strife::Core::Dispatcher& dispatcher)
    : ISystem(scene)
    , active_(true)
    , addComponentType_(scene_.components.get().begin()->first)
    , dispatcher_(dispatcher) {

	dispatcher.on<OnGui>([this](const OnGui& event) { render(event); });
}

EntityList::~EntityList() {}

void EntityList::render(const OnGui& event) {
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
			if(ImGui::Selectable("Add new entity")) {
				scene_.entities.add();
			}
			ImGui::EndPopup();
		}
		ImGui::BeginChild("Scrolling");
		optional<Entity> clickedEntity = nullopt;
		for (auto entity : scene_.entities.get()) {
			string entityId = boost::lexical_cast<string>(entity.id);
			bool selected = selectedEntities_.find(entity) != selectedEntities_.end();
			ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | (selected ? ImGuiTreeNodeFlags_Selected : 0);

			bool entityOpen = ImGui::TreeNodeEx(entityId.c_str(), node_flags);
			if (ImGui::IsItemClicked()) {
				clickedEntity = entity;
			}
			ImGui::PushID(entityId.c_str());

			bool openAddComponent = false;
			if (ImGui::BeginPopupContextItem("Entity context menu")) {
				if(ImGui::MenuItem("Add Component...")) {
					openAddComponent = true;
				}
				ImGui::EndPopup();
			}
			if (openAddComponent) {
				ImGui::OpenPopup("Add Component");
			}
			if (ImGui::BeginPopupModal("Add Component")) {

				if (ImGui::BeginCombo("Component Type", scene_.components.identifier(addComponentType_).c_str())) {
					for (auto& [type, storage] : scene_.components.get()) {
						string componentTypeName = scene_.components.identifier(type);
						if (ImGui::Selectable(componentTypeName.c_str(), type == addComponentType_)) {
							addComponentType_ = type;
						}
					}
					ImGui::EndCombo();
				}

				if (ImGui::Button("Add")) {
					entity.components.add(addComponentType_);
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::Button("Cancel")) {
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
			ImGui::PopID();
			if (entityOpen) {
				ImGui::TreePop();
			}
		}
		ImGui::EndChild();
		if (clickedEntity.has_value()) {
			if (!ImGui::GetIO().KeyCtrl) {
				selectedEntities_.clear();
				dispatcher_.emit<SelectEntity>(nullopt);
			}
			if (selectedEntities_.find(clickedEntity.value()) != selectedEntities_.end()) {
				selectedEntities_.erase(clickedEntity.value());
			} else {
				selectedEntities_.insert(clickedEntity.value());
				dispatcher_.emit<SelectEntity>(clickedEntity);
			}
		}
	}
	ImGui::End();
}
