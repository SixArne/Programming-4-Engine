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
#include "TextComponent.h"

void load()
{
	auto& scene = Engine::SceneManager::GetInstance().CreateScene("Demo");

	auto fpsCounter = std::make_shared<Engine::GameObject>();
	//go->SetTexture("background.tga");
	//scene.Add(go);

	//go = std::make_shared<Engine::GameObject>();
	//go->SetTexture("logo.tga");
	//go->SetPosition(216, 180);

	fpsCounter->AddComponent(new Engine::TextComponent{"Hello world"});
	//auto& component = fpsCounter->GetComponent<Engine::TextComponent>();

	//std::cout << component.GetText() << std::endl;

	scene.Add(fpsCounter);

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