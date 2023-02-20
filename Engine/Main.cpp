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
#include "TextObject.h"
#include "Scene.h"
#include "Core/ECS/TextComponent.h"
#include "Core/ECS/TextureRenderer.h"
#include "Core/ECS/TransformComponent.h"

void load()
{
	auto& scene = Engine::SceneManager::GetInstance().CreateScene("Demo");

	//auto fpsCounter = std::make_shared<Engine::GameObject>();
	
	// Create Background gameobject
	auto backgroundGO = std::make_shared<Engine::GameObject>();

	// TextureComponent
	auto textureComponent = new Engine::TextureRendererComponent();
	textureComponent->SetTexture("background.tga");

	// TransformComponent
	auto transformComponent = new Engine::TransformComponent();
	transformComponent->SetPosition(glm::vec2{ 0,0 });

	// Add components to background gameobject.
	backgroundGO->AddComponent(textureComponent);
	backgroundGO->AddComponent(transformComponent);

	// Add Background gameobject to scene.
	scene.Add(backgroundGO);




	//go = std::make_shared<Engine::GameObject>();
	//go->SetTexture("logo.tga");
	//go->SetPosition(216, 180);

	//fpsCounter->AddComponent(new Engine::TextComponent{"Hello world"});
	//auto component = fpsCounter->GetComponent<Engine::TextComponent>();

	//std::cout << component->GetText() << std::endl;

	//scene.Add(fpsCounter);

	//auto font = Engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<Engine::TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	//scene.Add(to);
}

int main(int, char*[]) {
	Engine::Engine engine("../Data/");
	engine.Run(load);
    return 0;
}