#include "ComponentList.h"

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

ComponentList::ComponentList(Strife::Core::Scene& scene, Strife::Core::Dispatcher& dispatcher)
    : ISystem(scene)
    , active_(true)
    , addComponentType_(scene_.components.get().begin()->first) {

	dispatcher.on<OnGui>([this](const OnGui& event) { render(event); });
	dispatcher.on<SelectEntity>([this](const SelectEntity& event) { selectEntity(event); });
}

ComponentList::~ComponentList() {}

bool renderTextInput(string& value, const string& fieldName) {
	std::string clipText = (ImGui::GetClipboardText() != nullptr) ? ImGui::GetClipboardText() : "";
	size_t clipSize = clipText.length();
	size_t size = value.length() + clipSize + 5;
	char* newText = static_cast<char*>(malloc(sizeof(char) * size));
	strncpy(newText, value.c_str(), size);

	bool textChanged = ImGui::InputText(fieldName.c_str(), newText, size);
	if (textChanged) {
		value = string(newText);
	}
	delete newText;
	return textChanged;
}

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

			if (renderTextInput(value, key)) {
				item = Data(value);
			}
			break;
	    }
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
	    case Data::value_t::boolean: {
		    bool* value = item.get<Data::boolean_t*>();
			if (ImGui::Checkbox(key.c_str(), value)) {
			}
			break;
	    }
	    case Data::value_t::null:
	    default:
		    ImGui::Text("%s", key.c_str());
			ImGui::Text("%s", item.dump().c_str());
	}
	return item;
}

void ComponentList::render(const OnGui& event) {
	if (ImGui::Begin("Components", &active_, ImGuiWindowFlags_MenuBar)) {
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
		for (auto currentEntity : currentEntities_) {
			ImGui::BeginChild("Scrolling");
			string entityId = boost::lexical_cast<string>(currentEntity.id);
			bool entityOpen = ImGui::TreeNode(entityId.c_str());
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
					currentEntity.components.add(addComponentType_);
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::Button("Cancel")) {
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
			ImGui::PopID();
			if (entityOpen) {
				for (auto& [type, storage] : scene_.components.get()) {
					auto component = storage->get(currentEntity);
					if (component != nullptr) {
						if (ImGui::TreeNode(scene_.components.identifier(type).c_str())) {
							Data componentData = component->serialize();
							Data modifiedData = renderData(componentData);
							EntityMap emap(scene_, true);
							component->deserialize(modifiedData, emap);
							ImGui::TreePop();
						}
					}
				}
				ImGui::TreePop();
				ImGui::Separator();
			}
			ImGui::EndChild();
		}
	}
	ImGui::End();
}

void ComponentList::selectEntity(const SelectEntity& event) {
	if (event.entity.has_value()) {
		currentEntities_.insert(*event.entity);
	} else {
		currentEntities_.clear();
	}
}
