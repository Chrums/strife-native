#include <iostream>
#include <fstream>

#include <boost/filesystem/path.hpp>

#include "Data.h"
#include "Sprite.h"
#include "Transform.h"
#include "events/RenderEvent.h"
#include "systems/SpriteAnimation.h"
#include "Scene.h"
#include "EntityMap.h"

using namespace std;
using namespace Strife::Core;
using boost::filesystem::path;

const string Sprite::Identifier = "Sprite";

void Sprite::Initialize(System<Sprite>& system) {
	system.on<RenderEvent>(&Sprite::render);
}

Sprite::Sprite(const Strife::Core::Entity& entity)
    : Component(entity)
    , texture_(nullptr) {}

Sprite::Sprite(const boost::uuids::uuid id, const Strife::Core::Entity& entity)
    : Component(id, entity)
    , texture_(nullptr) {}

const Data Sprite::serialize() const {
	Data data;
	data["dataFile"] = dataFile_;
	data["currentFrame"] = currentFrame_;
	data["frameTime"] = frameTime_;
    data["currentAnimation"] = animation_->name;
	return data;
}

void Sprite::deserialize(Data data, EntityMap& entityMap) {
	auto spriteSystem = entity.scene.systems.get<SpriteAnimation>();
	dataFile_ = data["dataFile"];
	currentFrame_ = data["currentFrame"];
	animation_ = &spriteSystem->getAnimation(dataFile_, data["currentAnimation"]);
	frameTime_ = data["frameTime"];
}

void Sprite::render(Event* event) {
	auto e = dynamic_cast<RenderEvent*>(event);
	if (texture_ == nullptr) {
		auto spriteSystem = entity.scene.systems.get<SpriteAnimation>();
		texture_ = spriteSystem->getTexture(dataFile_, e->renderer);
	}
	Frame* curFrame = animation_->frames[currentFrame_];

	SDL_Rect destRect;
	destRect.x = 0;
	destRect.y = 0;
	destRect.w = curFrame->w;
	destRect.h = curFrame->h;

	try {
		auto t = entity.components.get<Transform2f>();
		destRect.x = static_cast<int>(t->translation().x());
		destRect.y = static_cast<int>(t->translation().y());
	} catch (...) {
		// TODO: Should probably allow for requesting non existent Components w/o exception
	}

	SDL_RenderCopy(e->renderer, texture_, static_cast<SDL_Rect*>(curFrame), &destRect);

	frameTime_ += e->dt;
	if (frameTime_ >= animation_->frameLengths[currentFrame_]) {
		frameTime_ = 0;
		currentFrame_++;
		if (currentFrame_ >= animation_->frames.size()) {
			currentFrame_ = 0;
			animation_ = animation_->nextAnimation;
		}
	}
}

void Sprite::setAnimation(string animationName) {
	auto spriteSystem = entity.scene.systems.get<SpriteAnimation>();
	Animation* animation = &spriteSystem->getAnimation(dataFile_, animationName);
	if (animation != animation_) {
		animation_ = animation;
		currentFrame_ = 0;
		frameTime_ = 0;
	}
}

SDL_Texture* Sprite::loadTexture(string path, SDL_Renderer* renderer) {
	//The final texture
	SDL_Texture* newTexture = nullptr;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr) {
		cout << "Unable to load image " << path.c_str() << " " << IMG_GetError() << endl;
		throw std::runtime_error("Couldn't load texture");
	} else {
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == nullptr) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}
