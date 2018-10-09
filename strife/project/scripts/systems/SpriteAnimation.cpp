#include "SpriteAnimation.h"

#include <fstream>
#include <iostream>
#include <boost/filesystem/path.hpp>

using namespace std;
using namespace Strife::Core;
using namespace boost::filesystem;

void SpriteAnimation::loadSprite(string spritePath) {
    if (sprites_.find(spritePath) != sprites_.end()) {
        return;
    }
    sprites_[spritePath];
    SpriteData& sprite = sprites_.at(spritePath);
    Data imageData;
    try {
        ifstream file;
        file.open(spritePath);
        file >> imageData;
    } catch (exception& e) {
        cout << spritePath << " : " << e.what() << endl;
        throw runtime_error("Couldn't load sprite data");
    }

    for (auto frame : imageData["frames"].items()) {
        sprite.frames[frame.key()].deserialize(frame.value()["frame"]);
    }
    for (auto animation : imageData["animations"].items()) {
        Animation& anim = sprite.animations[animation.key()];
        for (auto frame : animation.value().at("frames")) {
            anim.frames.push_back(&sprite.frames.at(frame["name"]));
            anim.frameLengths.push_back(frame["length"]);
        }
    }
    for (auto animation : imageData["animations"].items()) {
        Animation& anim = sprite.animations[animation.key()];
        anim.nextAnimation = &sprite.animations[animation.value().at("next")];
    }
    sprite.textureWidth = imageData["meta"]["size"]["w"];
    sprite.textureHeight = imageData["meta"]["size"]["h"];
    path texturePath = spritePath;
    texturePath = texturePath.parent_path();
    string relativeTexturePath = imageData["meta"]["image"];
    texturePath /= relativeTexturePath;

    sprite.textureName = texturePath.string();
    sprite.texture = nullptr;
}

Animation& SpriteAnimation::getAnimation(string spriteName, string animationName) {
    loadSprite(spriteName);
    SpriteData& sprite = sprites_.at(spriteName);
    return sprite.animations.at(animationName);
}

SDL_Texture* SpriteAnimation::getTexture(string spriteName, SDL_Renderer* renderer) {
    loadSprite(spriteName);
    SpriteData& sprite = sprites_.at(spriteName);
    if (sprite.texture == nullptr) {
        sprite.texture = loadTexture(sprite.textureName, renderer);
    }
    return sprite.texture;
}

SDL_Texture* SpriteAnimation::loadTexture(string path, SDL_Renderer* renderer) {
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

const Data Frame::serialize() const {
    Strife::Core::Data data;
    data["x"] = x;
    data["y"] = y;
    data["w"] = w;
    data["h"] = h;
    return data;
}

void Frame::deserialize(Data data) {
    x = data["x"];
    y = data["y"];
    w = data["w"];
    h = data["h"];
}
