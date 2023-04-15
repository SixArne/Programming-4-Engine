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
#include "Scene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Core/Input/MoveCommands.h"
#include "Core/Input/InputManager.h"
#include "Core/Input/JumpCommand.h"
#include "Core/Input/DieCommand.h"
#include "Core/ECS/Custom/Mover.h"
#include "Core/ECS/TextureRenderer.h"
#include "Core/ECS/Custom/Rotator.h"
#include "Core/ECS/Custom/HealthComponent.h"
#include "Core/ECS/Custom/HealthIndicator.h"

#include "Core/Event/EventManager.h"

#pragma warning(push)
#pragma warning(disable: 4996)
#include <steam_api.h>
#pragma warning(pop)

void load()
{


	using Engine::InputState;
	using Engine::InputManager;
	using Engine::JumpCommand;
	using Engine::SceneManager;

	auto& scene = SceneManager::GetInstance().CreateScene("input");

	// Player 1
	auto playerConsole = std::make_shared<Engine::GameObject>("playerConsole", glm::vec2{ 100,100 });
	playerConsole->AddComponent<Engine::TextureRendererComponent>("Resources/Sprites/space_ship.png");
	auto consoleHealth = playerConsole->AddComponent<Engine::HealthComponent>();

	// Player 2
	auto playerDesktop = std::make_shared<Engine::GameObject>("playerRoot", glm::vec2{ 100,100 });
	playerDesktop->AddComponent<Engine::TextureRendererComponent>("Resources/Sprites/bug.png");
	auto desktopHealth = playerDesktop->AddComponent<Engine::HealthComponent>();

	// health
	auto playerHealthRoot = std::make_shared<Engine::GameObject>("PlayerHealth", glm::vec2{ 0, 0 });

	// player 1 health
	auto playerDesktopHealth = std::make_shared<Engine::GameObject>("PlayerDesktopHealth", glm::vec2{ 0,0 });
	auto desktopHealthIndicator = playerDesktopHealth->AddComponent<Engine::HealthIndicator>(desktopHealth->GetHealth());

	// player 2 health
	auto playerConsoleHealth = std::make_shared<Engine::GameObject>("PlayerConsoleHealth", glm::vec2{ 0,200 });
	auto consoleHealthIndicator = playerConsoleHealth->AddComponent<Engine::HealthIndicator>(consoleHealth->GetHealth());

	// Setup observers
	desktopHealth->RegisterObserver(desktopHealthIndicator->GetObserver());
	consoleHealth->RegisterObserver(consoleHealthIndicator->GetObserver());

	playerHealthRoot->AttachChild(playerDesktopHealth, false);
	playerHealthRoot->AttachChild(playerConsoleHealth, false);

	scene.Add(playerConsole);
	scene.Add(playerDesktop);
	scene.Add(playerHealthRoot);

	// Create controller
	InputManager::GetInstance().CreateController(0);

	// Console player
	InputManager::GetInstance().CreateConsoleCommand<Engine::ForwardCommand>(XINPUT_GAMEPAD_DPAD_UP, InputState::Hold, playerConsole.get());
	InputManager::GetInstance().CreateConsoleCommand<Engine::DownCommand>(XINPUT_GAMEPAD_DPAD_DOWN, InputState::Hold, playerConsole.get());
	InputManager::GetInstance().CreateConsoleCommand<Engine::LeftCommand>(XINPUT_GAMEPAD_DPAD_LEFT, InputState::Hold, playerConsole.get());
	InputManager::GetInstance().CreateConsoleCommand<Engine::RightCommand>(XINPUT_GAMEPAD_DPAD_RIGHT, InputState::Hold, playerConsole.get());
	InputManager::GetInstance().CreateConsoleCommand<Engine::DieCommand>(XINPUT_GAMEPAD_A, InputState::Press, playerConsole.get());

	// Desktop player
	InputManager::GetInstance().CreateDesktopCommand<Engine::ForwardCommand>(SDL_SCANCODE_UP, InputState::Hold, playerDesktop.get());
	InputManager::GetInstance().CreateDesktopCommand<Engine::DownCommand>(SDL_SCANCODE_DOWN, InputState::Hold, playerDesktop.get());
	InputManager::GetInstance().CreateDesktopCommand<Engine::LeftCommand>(SDL_SCANCODE_LEFT, InputState::Hold, playerDesktop.get());
	InputManager::GetInstance().CreateDesktopCommand<Engine::RightCommand>(SDL_SCANCODE_RIGHT, InputState::Hold, playerDesktop.get());
	InputManager::GetInstance().CreateDesktopCommand<Engine::DieCommand>(SDL_SCANCODE_F, InputState::Press, playerDesktop.get());
}

int main(int, char*[]) {

	Engine::Log::Init();

	if (!SteamAPI_Init())
	{
		L_ERROR("STEAM MUST BE RUNNING TO PLAY THIS");
		return -1;
	}


	Engine::Engine engine("../Data/");
	engine.Run(load);
    
	SteamAPI_Shutdown();
	
	return 0;
}