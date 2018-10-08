#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <stdexcept>

#include "Component.h"
#include "Entity.h"
#include "System.h"
#include "Event.h"

class Sprite : public Strife::Core::Component {

public:

    static void Initialize(Strife::Core::System<Sprite>& system);

    static const std::string Identifier;

    Sprite(const Strife::Core::Entity& entity);

    Sprite(const boost::uuids::uuid id, const Strife::Core::Entity& entity);

    const nlohmann::json serialize() const;

    void deserialize(nlohmann::json data);

    void render(Strife::Core::Event* event);

private:

    SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);

    struct Frame : public SDL_Rect {
        Uint32 length;

        const nlohmann::json serialize() const {
            nlohmann::json data;
            data["x"] = x;
            data["y"] = y;
            data["w"] = w;
            data["h"] = h;
            data["length"] = length;
            return data;
        }

        void deserialize(nlohmann::json data) {
            x = data["x"];
            y = data["y"];
            w = data["w"];
            h = data["h"];
            length = data["length"];
        }
    };

    SDL_Texture* texture_;
    std::string textureName_;
    Uint32 textureWidth_;
    Uint32 textureHeight_;
    std::vector<Frame> frames_;
    Uint32 currentFrame_;
    Uint32 frameTime_;

};

#endif // SPRITE_H
