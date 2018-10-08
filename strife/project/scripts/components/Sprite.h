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

class Sprite : public Strife::Core::Component {

public:

    static void Initialize(Strife::Core::System<Sprite>& system);

    static const std::string Identifier;

    Sprite(const Strife::Core::Entity& entity);

    Sprite(const boost::uuids::uuid id, const Strife::Core::Entity& entity);

    const Strife::Core::Data serialize() const;

    void deserialize(Strife::Core::Data data);

    void render(Strife::Core::Event* event);

private:

    SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);

    struct Frame : public SDL_Rect {

        const nlohmann::json serialize() const {
            nlohmann::json data;
            data["x"] = x;
            data["y"] = y;
            data["w"] = w;
            data["h"] = h;
            return data;
        }

        void deserialize(nlohmann::json data) {
            x = data["x"];
            y = data["y"];
            w = data["w"];
            h = data["h"];
        }
    };

    SDL_Texture* texture_;
    std::string textureName_;
    Uint32 textureWidth_;
    Uint32 textureHeight_;
    std::vector<Frame> frames_;

    std::string dataFile_;
    Uint32 currentFrame_;
    Uint32 frameTime_;

};

#endif // SPRITE_H
