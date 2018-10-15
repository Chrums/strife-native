#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <stdexcept>

#include "Component.h"
#include "Data.h"
#include "Entity.h"
#include "System.h"
#include "Event.h"
#include "events/RenderEvent.h"
#include "EntityMap.h"
#include "systems/SpriteAnimation.h"

class Sprite : public Strife::Core::Component {

public:
	static void Initialize(Strife::Core::System<Sprite>& system);

	static const std::string Identifier;

	Sprite(const Strife::Core::Entity& entity);

	Sprite(const boost::uuids::uuid id, const Strife::Core::Entity& entity);

	const Strife::Core::Data serialize() const;

    void deserialize(Strife::Core::Data data, Strife::Core::EntityMap& entityMap);
    void deserializer(Strife::Core::Data data, Strife::Core::EntityMap& entityMap);

	void render(const RenderEvent& event);

	void setAnimation(std::string path);

    const Strife::Core::Data serializer() const;

private:
	SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);

	SDL_Texture* texture_;
	Animation* animation_;

	std::string dataFile_;
	Uint32 currentFrame_;
    Uint32 frameTime_;
};

void from_json(const nlohmann::json& j, Sprite& obj);
void to_json(nlohmann::json& j, const Sprite& obj);

#endif  // SPRITE_H
