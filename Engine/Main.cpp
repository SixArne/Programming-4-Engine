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
#include "Scenes/TrashTheCacheScene.h"

void load()
{
	//auto rotatorScene = std::make_shared<Engine::RotatorScene>("RotatorScene");
	auto benchMarkScene = std::make_shared<Engine::TrashTheCacheScene>("TrashTheCache");

	Engine::SceneManager::GetInstance().AddScene(benchMarkScene);
}

int main(int, char*[]) {
	Engine::Log::Init();

	Engine::Engine engine("../Data/");
	engine.Run(load);
    return 0;
}