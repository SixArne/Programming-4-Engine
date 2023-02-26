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

	//auto fpsCounter = std::make_shared<Engine::GameObject>();
	
	// Create Background gameobject
	auto backgroundGO = std::make_shared<Engine::GameObject>("Background");

	// TextureComponent
	auto bgTextureComponent = new Engine::TextureRendererComponent();
	bgTextureComponent->SetTexture("background.tga");

	// TransformComponent
	auto bgTransformComponent = new Engine::TransformComponent();
	bgTransformComponent->SetPosition(glm::vec2{ 0,0 });

	// TextRenderComponent
	auto font = Engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto bgTextRenderComponent = new Engine::TextComponent("Hello world", font);

	// Add components to background gameobject.
	backgroundGO->AddComponent(bgTextureComponent);
	backgroundGO->AddComponent(bgTransformComponent);
	backgroundGO->AddComponent(bgTextRenderComponent);

	// Add Background gameobject to scene.
	scene.Add(backgroundGO);

	auto fpsCounter = std::make_shared<Engine::GameObject>("fpsCounter");

	auto fpsTransformComponent = new Engine::TransformComponent();
	fpsTransformComponent->SetPosition(glm::vec2{ 100,50 });

	auto fpsTextRenderComponent = new Engine::TextComponent("Hello world", font);
	auto fpsComponent = new Engine::FPSCounter();

	fpsTextRenderComponent->GetText();

	fpsCounter->AddComponent(fpsTransformComponent);
	fpsCounter->AddComponent(fpsTextRenderComponent);
	fpsCounter->AddComponent(fpsComponent);

	scene.Add(fpsCounter);

}

int main(int, char*[]) {
	Engine::Log::Init();

	Engine::Engine engine("../Data/");
	engine.Run(load);
    return 0;
}