#include <iostream>

#include "Sprite.h"
#include "Transform.h"
#include "events/RenderEvent.h"

using namespace std;
using namespace Strife::Core;

const string Sprite::Identifier = "Sprite";


void Sprite::Initialize(System<Sprite> &system) {
    system.on<RenderEvent>(&Sprite::render);
}

Sprite::Sprite(const Strife::Core::Entity &entity) :
    texture_(nullptr), Component(entity) {}

Sprite::Sprite(const boost::uuids::uuid id, const Strife::Core::Entity &entity) :
    texture_(nullptr), Component(id, entity) {}

const nlohmann::json Sprite::serialize() const {
    nlohmann::json data;
    //data["data"] = Serialization::SerializeMatrix<T, D+1, D+1>(this->matrix());
    return data;
}

void Sprite::deserialize(nlohmann::json data) {
    frames_.resize(data["frames"].size());
    Uint32 frameNum = 0;
    for (auto frame : data["frames"]) {
        frames_[frameNum++].deserialize(frame);
    }
    textureWidth_ = data["textureWidth"];
    textureHeight_ = data["textureHeight"];
    textureName_ = data["textureName"];
    currentFrame_ = data["currentFrame"];
    frameTime_ = data["frameTime"];
}

void Sprite::render(Event *event) {
    Frame f;
    f.x = 0;
    f.y = 0;
    f.w = 16;
    f.h = 16;
    f.length = 200;
    frames_.push_back(f);
    textureName_ = "assets/images/ball.png";
    textureWidth_ = 32;
    textureHeight_ = 32;
    currentFrame_ = 0;


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
