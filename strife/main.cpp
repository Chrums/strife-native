#include <iostream>
#include <fstream>

#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
#include <SDL.h>
#include <SDL_ttf.h>
#include <imgui.h>
#include "Component.h"
#include "Dispatcher.h"
#include "Engine.h"
#include "Entity.h"
#include "Event.h"
#include "Messenger.h"
#include "Scene.h"
#include "Storage.h"
#include "IStorage.h"
#include "System.h"
#include "EntityMap.h"

#include "components/Transform.h"
#include "components/Sprite.h"
#include "components/Hierarchy.h"

#include "events/RenderEvent.h"
#include "events/UpdateEvent.h"
#include "events/BeginGui.h"
#include "events/OnGui.h"
#include "events/FinishGui.h"

#include "systems/SpriteAnimation.h"
#include "systems/ImguiSystem.h"
#include "systems/EntityList.h"

#include "utility/imgui_impl_sdl.h"
#include "utility/imgui_impl_opengl3.h"
#include "utility/imgui_sdl.h"

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

class BeginRenderEvent : public Event {

public:
	static const unsigned int Priority;

	BeginRenderEvent(SDL_Renderer* renderer)
	    : renderer(renderer) {}

	SDL_Renderer* renderer;
};

const unsigned int BeginRenderEvent::Priority = 900;

class FinishRenderEvent : public Event {

public:
	static const unsigned int Priority;

	FinishRenderEvent(SDL_Window* window, SDL_Renderer* renderer)
	    : window(window)
	    , renderer(renderer) {}

	SDL_Window* window;
	SDL_Renderer* renderer;
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

	void render(const RenderEvent& event) {
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = 32;
		rect.h = 32;

		auto t = entity.components.get<Transform2f>();
		if (t != nullptr) {
			rect.x = static_cast<int>(t->translation().x());
			rect.y = static_cast<int>(t->translation().y());
		}

		SDL_SetRenderDrawColor(event.renderer, 200, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(event.renderer, &rect);
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

	const Data serialize() const {
		Data data;
		data["xSpeed"] = xSpeed;
		data["ySpeed"] = ySpeed;
		return data;
	}

	void deserialize(Data data, EntityMap& entityMap) {
		xSpeed = data["xSpeed"];
		ySpeed = data["ySpeed"];
	}

	void update(const UpdateEvent& event) {
		auto t = entity.components.get<Transform2f>();
		if (t != nullptr) {
			t->translation().x() += xSpeed;
			t->translation().y() += ySpeed;
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
	bool isTrue;

	using Component::Component;

	const Data serialize() const {
		Data data;
		data["value"] = value;
		data["isTrue"] = isTrue;
		return data;
	}

	void deserialize(Data data, EntityMap& entityMap) {
		value = data["value"];
		isTrue = data["isTrue"];
	}

	void handleEvent(const TestEvent& event) {
		cout << "data:" << event.data << " " << entity.id << " " << value << endl;
	}

	void update(const UpdateEvent& event) {

		auto v = entity.components.get<Velocity>();
		auto sprite = entity.components.get<Sprite>();
		if (v != nullptr && sprite != nullptr) {
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
			if (state[SDL_SCANCODE_SPACE]) {
				cout << "sp" << endl;
				try {
					std::ifstream file;
					file.open("assets/scenes/default.json");
					json j;
					file >> j;
					scene.deserialize(j);
				} catch (exception& e) {
					cout << e.what() << endl;
				}
			}
		}
	}

	void collision(const CollisionEvent& event) {}
};

const string TestComponent::Identifier = "Test";

class RenderSystem : public ISystem {

public:
	RenderSystem(Strife::Core::Scene& scene, Dispatcher& dispatcher)
	    : ISystem(scene)
	    , dispatcher_(dispatcher) {

		dispatcher_.on<BeginRenderEvent>([this](const BeginRenderEvent& event) { beginRender(event); });
		dispatcher_.on<FinishRenderEvent>([this](const FinishRenderEvent& event) { finishRender(event); });
	}

	virtual void initialize() {}

	~RenderSystem() {}

	void beginRender(const BeginRenderEvent& event) {
		SDL_SetRenderDrawColor(event.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(event.renderer);
	}

	void finishRender(const FinishRenderEvent& event) {
		SDL_RenderPresent(event.renderer);
	}

private:
	Dispatcher& dispatcher_;
};

class PhysicsSystem : public ISystem {

public:
	PhysicsSystem(Strife::Core::Scene& scene, Dispatcher& dispatcher)
	    : ISystem(scene)
	    , dispatcher_(dispatcher) {

		dispatcher_.on<FindCollisionsEvent>([this](const FindCollisionsEvent& event) { findCollisions(event); });
	}

	virtual void initialize() {}

	~PhysicsSystem() {}

	void findCollisions(const FindCollisionsEvent& event) {
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
						dispatcher_.emit<CollisionEvent>(transformA->entity, transformB->entity);
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

	// Messenger m;

	// auto test =
	// 	[=](const TestEvent& event) {
	// 		cout << event.data << endl;
	// 	};

	// auto update =
	// 	[=](const UpdateEvent& event) {
	// 		cout << event.data << endl;
	// 	};

	// m.on<TestEvent>(test);
	// m.on<UpdateEvent>(update);

	// TestEvent tester;
	// tester.data = "Test!";

	// UpdateEvent updater;
	// updater.data = "Update!";

	// m.emit(tester);
	// m.emit(updater);
	// m.emit(updater);

	Strife::Core::Scene* s = new Strife::Core::Scene(Engine::Instance()->dispatcher);
	s->initialize<TestComponent>();
	s->initialize<Transform2f>();
	s->initialize<DrawSquare>();
	s->initialize<Velocity>();
	s->initialize<Sprite>();
	s->initialize<Hierarchy>();
	s->systems.initialize<RenderSystem>();
	s->systems.initialize<PhysicsSystem>();
	s->systems.initialize<SpriteAnimation>();
	ImguiSystem& imguiSystem = s->systems.initialize<ImguiSystem>();
	s->systems.initialize<EntityList>();

	//	Entity e0(*s);
	//	TestComponent* t0 = e0.components.add<TestComponent>();
	//	Transform2f* tr0 = e0.components.add<Transform2f>();
	//	Sprite* sp0 = e0.components.add<Sprite>();
	//    EntityMap entityMap(*s);
	//    sp0->deserialize("{\"dataFile\": \"assets/images/ball.json\", \"currentFrame\": 0, \"frameTime\": 0, \"currentAnimation\": \"bounce\"}"_json, entityMap);
	//	e0.components.add<Velocity>();
	//	tr0->translation().x() = 60;
	//	cout << t0->entity.id << " t0id " << tr0->translation().x() << endl;
	//	t0->value = "0";

	//	Entity e1(*s);
	//	Transform2f* tr1 = e1.components.add<Transform2f>();
	//	auto v1 = e1.components.add<Velocity>();
	//	e1.components.add<DrawSquare>();
	//	Sprite* sp1 = e1.components.add<Sprite>();
	//    sp1->deserialize("{\"dataFile\": \"assets/images/numbers.json\", \"currentFrame\": 0, \"frameTime\": 0, \"currentAnimation\": \"count\"}"_json, entityMap);
	//	v1->ySpeed = 0.25f;

	try {
		std::ifstream file;
		file.open("assets/scenes/default.json");
		json j;
		file >> j;
		s->deserialize(j);
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	// s->deserialize("{\"components\":{\"Test\":{\"60a7adcb-8f76-438c-b95b-150f00507f41\":{\"value\":\"0\",\"x\":0},\"e3140528-624b-4529-991a-423b03ed69a2\":{\"value\":\"1\",\"x\":60}}}}"_json);

	json data = s->serialize();
	cout << data << endl;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("SDL2Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);

	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	IMGUI_CHECKVERSION();
	imguiSystem.init(renderer);

	ImGui_ImplSDL2_InitForOpenGL(window);

	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 100, 100);
	{
		SDL_SetRenderTarget(renderer, texture);
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderTarget(renderer, nullptr);
	}

	ImGuiIO& io = ImGui::GetIO();

	// Setup style

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;

	Uint32 startTime = SDL_GetTicks();

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			ImGui_ImplSDL2_ProcessEvent(&e);  //TODO: Move to system
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
		imguiSystem.handleMouse(window);

		// Setup low-level inputs (e.g. on Win32, GetKeyboardState(), or write to those fields from your Windows message loop handlers, etc.)

		io.DeltaTime = 1.0f / 60.0f;

		Engine::Instance()->dispatcher.emit<UpdateEvent>(16);
		Engine::Instance()->dispatcher.emit<FindCollisionsEvent>();
		Engine::Instance()->dispatcher.emit<BeginRenderEvent>(renderer);
		Engine::Instance()->dispatcher.emit<RenderEvent>(renderer, 16);
		Engine::Instance()->dispatcher.emit<BeginGui>();
		Engine::Instance()->dispatcher.emit<OnGui>();
		Engine::Instance()->dispatcher.emit<FinishGui>();
		Engine::Instance()->dispatcher.emit<FinishRenderEvent>(window, renderer);
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
