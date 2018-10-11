#include <iostream>
#include <fstream>

#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
#include <SDL.h>
#include "Component.h"
#include "Dispatcher.h"
#include "Engine.h"
#include "Entity.h"
#include "Event.h"
#include "Scene.h"
#include "Storage.h"
#include "IStorage.h"
#include "System.h"

#include "components/Transform.h"
#include "components/Sprite.h"

#include "events/RenderEvent.h"

#include "systems/SpriteAnimation.h"

using namespace Strife::Core;
using namespace std;
using boost::uuids::uuid;
using nlohmann::json;

class TestEvent : public Event {

public:
	using Event::Event;

	static const unsigned int Priority;

	string data;
};

const unsigned int TestEvent::Priority = 10;

class UpdateEvent : public Event {

public:
	using Event::Event;

	static const unsigned int Priority;

	string data;
};

const unsigned int UpdateEvent::Priority = 500;

class BeginRenderEvent : public Event {

public:
	using Event::Event;

	static const unsigned int Priority;

	SDL_Renderer* renderer;
};

const unsigned int BeginRenderEvent::Priority = 900;

class FinishRenderEvent : public Event {

public:
	using Event::Event;

	static const unsigned int Priority;

	SDL_Window* window;
};

const unsigned int FinishRenderEvent::Priority = 1100;

class FindCollisionsEvent : public Event {

public:
	using Event::Event;

	static const unsigned int Priority;
};

const unsigned int FindCollisionsEvent::Priority = 400;

class CollisionEvent : public Event {

public:
	const Entity other;

	CollisionEvent(Entity entity, Entity other)
	    : Event(entity)
	    , other(other) {}

	static const unsigned int Priority;
};

const unsigned int CollisionEvent::Priority = 410;

void makeTestEvent(TestEvent& event) {
	event.data = "HI!";
}

class DrawSquare : public Component {

public:
	static void Initialize(System<DrawSquare>& system) {
		system.on<RenderEvent>(&DrawSquare::render);
	}

	static const string Identifier;

	using Component::Component;

	void render(Event* event) {
		auto e = dynamic_cast<RenderEvent*>(event);
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = 32;
		rect.h = 32;

		try {
			auto t = entity.components.get<Transform2f>();
			rect.x = t->translation().x();
			rect.y = t->translation().y();
		} catch (const std::exception& e) {
			// TODO: Should probably allow for requesting non existent Components w/o exception
		}

		SDL_SetRenderDrawColor(e->renderer, 200, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(e->renderer, &rect);
	}
};

const string DrawSquare::Identifier = "DrawSquare";

class Velocity : public Component {

public:
	static void Initialize(System<Velocity>& system) {
		system.on<UpdateEvent>(&Velocity::update);
	}

	static const string Identifier;

	using Component::Component;

	float xSpeed = 0;
	float ySpeed = 0;

	const json serialize() const {
		json data;
		data["xSpeed"] = xSpeed;
		data["ySpeed"] = ySpeed;
		return data;
	}

	void deserialize(json data) {
		xSpeed = data["xSpeed"];
		ySpeed = data["ySpeed"];
	}

	void update(Event* event) {
		try {
			auto t = entity.components.get<Transform2f>();
			t->translation().x() += xSpeed;
			t->translation().y() += ySpeed;
		} catch (const std::exception& e) {
			// TODO: Should probably allow for requesting non existent Components w/o exception
		}
	}
};

const string Velocity::Identifier = "Velocity";

class TestComponent : public Component {

public:
	static void Initialize(System<TestComponent>& system) {
		system.on<TestEvent>(&TestComponent::handleEvent);
		system.on<UpdateEvent>(&TestComponent::update);
		system.on<CollisionEvent>(&TestComponent::collision);
	}

	static const string Identifier;

	string value;

	using Component::Component;

	const json serialize() const {
		json data;
		data["value"] = value;
		return data;
	}

	void deserialize(json data) {
		value = data["value"];
	}

	void handleEvent(Event* event) {
		auto e = dynamic_cast<TestEvent*>(event);
		cout << "data:" << e->data << " " << entity.id << " " << value << endl;
	}

	void update(Event* event) {
		auto e = dynamic_cast<UpdateEvent*>(event);

		try {
			auto v = entity.components.get<Velocity>();
			auto sprite = entity.components.get<Sprite>();
			v->xSpeed = 0;
			v->ySpeed = 0;
			const Uint8* state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_RIGHT]) {
				v->xSpeed = 1;
				sprite->setAnimation("bounce");
			}
			if (state[SDL_SCANCODE_LEFT]) {
				v->xSpeed = -1;
				sprite->setAnimation("bounce");
			}
			if (state[SDL_SCANCODE_UP]) {
				v->ySpeed = -1;
				sprite->setAnimation("bounce");
			}
			if (state[SDL_SCANCODE_DOWN]) {
				v->ySpeed = 1;
				sprite->setAnimation("bounce");
			}
		} catch (const std::exception& e) {
			// TODO: Should probably allow for requesting non existent Components w/o exception
		}
	}

	void collision(Event* event) {
		auto e = dynamic_cast<CollisionEvent*>(event);
		cout << "collided!: " << e->other.id << endl;
	}
};

const string TestComponent::Identifier = "Test";

class RenderSystem : public ISystem {

public:
	RenderSystem(Strife::Core::Scene& scene, Dispatcher& dispatcher)
	    : ISystem(scene)
	    , dispatcher_(dispatcher) {

		dispatcher_.initialize<BeginRenderEvent>();
		dispatcher_.initialize<FinishRenderEvent>();

		dispatcher_.on<BeginRenderEvent>([this](Event* event, std::type_index type) { beginRender(event, type); });
		dispatcher_.on<FinishRenderEvent>([this](Event* event, std::type_index type) { finishRender(event, type); });
	}

	virtual void initialize() {}

	~RenderSystem() {}

	void beginRender(Event* event, std::type_index eventType) {
		BeginRenderEvent* e = dynamic_cast<BeginRenderEvent*>(event);

		SDL_SetRenderDrawColor(e->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(e->renderer);
	}

	void finishRender(Event* event, std::type_index eventType) {
		FinishRenderEvent* e = dynamic_cast<FinishRenderEvent*>(event);

		SDL_UpdateWindowSurface(e->window);
	}

private:
	Dispatcher& dispatcher_;
};

class PhysicsSystem : public ISystem {

public:
	PhysicsSystem(Strife::Core::Scene& scene, Dispatcher& dispatcher)
	    : ISystem(scene)
	    , dispatcher_(dispatcher) {

		dispatcher_.initialize<FindCollisionsEvent>();

		dispatcher_.on<FindCollisionsEvent>([this](Event* event, std::type_index type) { findCollisions(event, type); });
	}

	virtual void initialize() {}

	~PhysicsSystem() {}

	void findCollisions(Event* event, std::type_index eventType) {
		auto transforms = this->scene_.components.get<Transform2f>();
		for (auto tA : *transforms) {
			auto transformA = static_cast<Transform2f*>(tA.second);
			for (auto tB : *transforms) {
				auto transformB = static_cast<Transform2f*>(tB.second);
				if (((transformA->translation().x() <= transformB->translation().x() + 32 && transformA->translation().x() >= transformB->translation().x()) &&
				     (transformA->translation().y() <= transformB->translation().y() + 32 && transformA->translation().y() >= transformB->translation().y())) ||
				    ((transformB->translation().x() <= transformA->translation().x() + 32 && transformB->translation().x() >= transformA->translation().x()) &&
				     (transformB->translation().y() <= transformA->translation().y() + 32 && transformB->translation().y() >= transformA->translation().y()))) {

					if (transformA->entity.id != transformB->entity.id) {
						CollisionEvent* ev = new CollisionEvent(transformA->entity, transformB->entity);
						dispatcher_.trigger(std::type_index(typeid(CollisionEvent)), ev, CollisionEvent::Priority);
					}
				}
			}
		}
	}

private:
	Dispatcher& dispatcher_;
};

// class Ultima : public Engine {

//     void initialize(Scene scene) {
//         scene.components.initialize<Test>();
//     }

// };

int main() {

	Strife::Core::Scene* s = new Strife::Core::Scene(Engine::Instance()->dispatcher);
	s->initialize<TestComponent>();
	s->initialize<Transform2f>();
	s->initialize<DrawSquare>();
	s->initialize<Velocity>();
	s->initialize<Sprite>();
	s->systems.initialize<RenderSystem>();
	s->systems.initialize<PhysicsSystem>();
	s->systems.initialize<SpriteAnimation>();

	Entity e0(*s);
	TestComponent* t0 = e0.components.add<TestComponent>();
	Transform2f* tr0 = e0.components.add<Transform2f>();
	Sprite* sp0 = e0.components.add<Sprite>();
	sp0->deserialize("{\"dataFile\": \"assets/images/ball.json\", \"currentFrame\": 0, \"frameTime\": 0, \"currentAnimation\": \"bounce\"}"_json);
	e0.components.add<Velocity>();
	tr0->translation().x() = 60;
	cout << t0->entity.id << " t0id " << tr0->translation().x() << endl;
	t0->value = "0";

	Entity e1(*s);
	Transform2f* tr1 = e1.components.add<Transform2f>();
	auto v1 = e1.components.add<Velocity>();
	e1.components.add<DrawSquare>();
	Sprite* sp1 = e1.components.add<Sprite>();
	sp1->deserialize("{\"dataFile\": \"assets/images/numbers.json\", \"currentFrame\": 0, \"frameTime\": 0, \"currentAnimation\": \"count\"}"_json);
	v1->ySpeed = 0.25f;

	//    try {
	//        std::ifstream file;
	//        file.open("strife/project/scenes/default.json");
	//        json j;
	//        file >> j;
	//        s->deserialize(j);
	//    } catch (exception& e) {
	//        cout << e.what() << endl;
	//    }

	// s->deserialize("{\"components\":{\"Test\":{\"60a7adcb-8f76-438c-b95b-150f00507f41\":{\"value\":\"0\",\"x\":0},\"e3140528-624b-4529-991a-423b03ed69a2\":{\"value\":\"1\",\"x\":60}}}}"_json);

	json data = s->serialize();
	cout << data << endl;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("SDL2Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	auto makeRenderEvent = [=](RenderEvent& event) {
		event.renderer = renderer;
		event.dt = 16;
	};
	auto makeBeginRenderEvent = [=](BeginRenderEvent& event) { event.renderer = renderer; };
	auto makeFinishRenderEvent = [=](FinishRenderEvent& event) { event.window = window; };

	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;

	Uint32 startTime = SDL_GetTicks();

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		//Engine::Instance()->dispatcher.trigger<TestEvent>(makeTestEvent);
		Engine::Instance()->dispatcher.trigger<UpdateEvent>();
		Engine::Instance()->dispatcher.trigger<FindCollisionsEvent>();
		Engine::Instance()->dispatcher.trigger<RenderEvent>(makeRenderEvent);
		Engine::Instance()->dispatcher.trigger<BeginRenderEvent>(makeBeginRenderEvent);
		Engine::Instance()->dispatcher.trigger<FinishRenderEvent>(makeFinishRenderEvent);
		Engine::Instance()->dispatcher.dispatch();

		Uint32 runTime = SDL_GetTicks() - startTime;

		if (runTime < 16) {
			Uint32 delayTime = 16 - runTime;
			SDL_Delay(delayTime);
		}
		startTime = SDL_GetTicks();
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	delete s;

	return 0;
}
