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

void load()
{
	auto& scene = Engine::SceneManager::GetInstance().CreateScene("Demo");
	auto fpsCounter = std::make_shared<Engine::GameObject>("fpsCounter");

	fpsCounter->AddComponent<Engine::TransformComponent>();
	fpsCounter->AddComponent<Engine::TextComponent>();
	fpsCounter->AddComponent<Engine::FPSCounter>();

	scene.Add(fpsCounter);
}

int main(int, char*[]) {
	Engine::Log::Init();

	Engine::Engine engine("../Data/");
	engine.Run(load);
    return 0;
}