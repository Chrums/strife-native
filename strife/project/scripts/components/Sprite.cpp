#include <iostream>
#include <fstream>

#include <boost/filesystem/path.hpp>

#include "Data.h"
#include "Sprite.h"
#include "Transform.h"
#include "events/RenderEvent.h"

using namespace std;
using namespace Strife::Core;
using boost::filesystem::path;

const string Sprite::Identifier = "Sprite";


void Sprite::Initialize(System<Sprite> &system) {
    system.on<RenderEvent>(&Sprite::render);
}

Sprite::Sprite(const Strife::Core::Entity &entity) :
    texture_(nullptr), Component(entity) {}

Sprite::Sprite(const boost::uuids::uuid id, const Strife::Core::Entity &entity) :
    texture_(nullptr), Component(id, entity) {}

const Data Sprite::serialize() const {
    Data data;
    data["dataFile"] = dataFile_;
    data["currentFrame"] = currentFrame_;
    data["frameTime"] = frameTime_;
    return data;
}

void Sprite::deserialize(Data data) {
    dataFile_ = data["dataFile"];
    currentFrame_ = data["currentFrame"];
    frameTime_ = data["frameTime"];

    // TODO: Move animation data to system
    Data imageData;
    try {
        std::ifstream file;
        file.open(dataFile_);
        file >> imageData;
    } catch (exception& e) {
        cout << dataFile_ << " : " << e.what() << endl;
        throw std::runtime_error("Couldn't load image data");
    }

    frames_.resize(imageData["frames"].size());
    Uint32 frameNum = 0;
    for (auto frame : imageData["frames"].items()) {
        frames_[frameNum++].deserialize(frame.value()["frame"]);
    }
    textureWidth_ = imageData["meta"]["size"]["w"];
    textureHeight_ = imageData["meta"]["size"]["h"];
    path texturePath = dataFile_;
    texturePath = texturePath.parent_path();
    string relativeTexturePath = imageData["meta"]["image"];
    texturePath /= relativeTexturePath;

    textureName_ = texturePath.string();
}

void Sprite::render(Event *event) {
    auto e = dynamic_cast<RenderEvent*>(event);
    if (texture_ == nullptr) {
        texture_ = loadTexture(textureName_, e->renderer);
    }
    Frame* curFrame = &frames_[currentFrame_];

    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = curFrame->w;
    destRect.h = curFrame->h;

    try {
        auto t = entity.components.get<Transform2f>();
        destRect.x = (int)t->translation().x();
        destRect.y = (int)t->translation().y();
    } catch (...) {
        // TODO: Should probably allow for requesting non existent Components w/o exception
    }

    SDL_RenderCopy(e->renderer, texture_, static_cast<SDL_Rect*>(curFrame), &destRect );
}

SDL_Texture *Sprite::loadTexture(string path, SDL_Renderer *renderer) {
    //The final texture
    SDL_Texture* newTexture = nullptr;
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if(loadedSurface == nullptr) {
        cout << "Unable to load image " << path.c_str() << " " << IMG_GetError() << endl;
        throw std::runtime_error("Couldn't load texture");
    } else {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == nullptr ) {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}
