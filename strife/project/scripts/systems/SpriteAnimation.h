#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include <string>
#include <unordered_map>
#include <SDL.h>
#include <SDL_image.h>

#include "Data.h"
#include "System.h"
#include "Dispatcher.h"

class Scene;

struct Frame : public SDL_Rect {

    const Strife::Core::Data serialize() const {
        Strife::Core::Data data;
        data["x"] = x;
        data["y"] = y;
        data["w"] = w;
        data["h"] = h;
        return data;
    }

    void deserialize(Strife::Core::Data data) {
        x = data["x"];
        y = data["y"];
        w = data["w"];
        h = data["h"];
    }
};

struct Animation {
    Animation* nextAnimation;
    std::vector<Frame*> frames;
    std::vector<Uint32> frameLengths;
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

    SpriteAnimation(Strife::Core::Scene* const scene, Strife::Core::Dispatcher& dispatcher) :
        ISystem(scene) {
    }

    virtual void initialize() {
    }

    ~SpriteAnimation() {

    }

    void loadSprite(std::string spritePath);

    Animation& getAnimation(std::string spriteName, std::string animationName);

    SDL_Texture* getTexture(std::string spriteName, SDL_Renderer* renderer);

private:
    std::unordered_map<std::string, SpriteData> sprites_;

    SDL_Texture* loadTexture(std::string path, SDL_Renderer *renderer);
};

#endif
