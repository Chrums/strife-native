#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include <string>
#include <unordered_map>
#include <SDL.h>
#include <SDL_image.h>

#include "Data.h"
#include "System.h"
#include "Dispatcher.h"
#include "EntityMap.h"

class Scene;

struct Frame : public SDL_Rect {
	const Strife::Core::Data serialize() const;
    void deserialize(Strife::Core::Data data, Strife::Core::EntityMap& entityMap);
};

struct Animation {
	Animation* nextAnimation;
	std::vector<Frame*> frames;
	std::vector<Uint32> frameLengths;
    std::string name;
};

struct SpriteData {
	SDL_Texture* texture;
	std::string textureName;
	Uint32 textureWidth;
	Uint32 textureHeight;
	std::unordered_map<std::string, Frame> frames;
	std::unordered_map<std::string, Animation> animations;
};

class SpriteAnimation : public Strife::Core::ISystem {

public:
	SpriteAnimation(Strife::Core::Scene& scene, Strife::Core::Dispatcher& dispatcher)
	    : ISystem(scene) {}

	virtual void initialize() {}

	~SpriteAnimation() = default;

	void loadSprite(std::string spritePath);

	Animation& getAnimation(std::string spriteName, std::string animationName);

	SDL_Texture* getTexture(std::string spriteName, SDL_Renderer* renderer);

private:
	std::unordered_map<std::string, SpriteData> sprites_;

	SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);
};

#endif
