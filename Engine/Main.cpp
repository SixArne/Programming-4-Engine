#include "pch.h"

#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Engine.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Core/ECS/TextComponent.h"
#include "Core/ECS/TextureRenderer.h"
#include "Core/ECS/TransformComponent.h"
#include "Core/ECS/Custom/FPSCounter.h"
#include "Core/ECS/Custom/Rotator.h"

void load()
{
	auto& scene = Engine::SceneManager::GetInstance().CreateScene("Demo");

	// FPS component
	auto fpsCounter = std::make_shared<Engine::GameObject>("fpsCounter", glm::vec2{ 500, 0 });
	fpsCounter->AddComponent<Engine::TextComponent>();
	fpsCounter->AddComponent<Engine::FPSCounter>();

	// Spaces ship
	auto spaceShip = std::make_shared<Engine::GameObject>("spaceShip", glm::vec2{ 100,100 });
	spaceShip->AddComponent<Engine::TextureRendererComponent>("Resources/Sprites/space_ship.png");
	spaceShip->AddComponent<Engine::Rotator>();

	// Bug
	auto bug = std::make_shared<Engine::GameObject>("bug", glm::vec2{0, 20});
	bug->AddComponent<Engine::TextureRendererComponent>("Resources/Sprites/bug.png");
	bug->AddComponent<Engine::Rotator>();

	bug->SetParent(spaceShip.get(), false);

	bug->RemoveComponent<Engine::TransformComponent>();

	scene.Add(bug);
	scene.Add(spaceShip);
	//scene.Add(fpsCounter);
}

int main(int, char*[]) {
	Engine::Log::Init();

	Engine::Engine engine("../Data/");
	engine.Run(load);
    return 0;
}