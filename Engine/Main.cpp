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
#include "Core/Input/PointCommand.h"
#include "Core/ECS/Custom/Mover.h"
#include "Core/ECS/TextureRenderer.h"
#include "Core/ECS/Custom/Rotator.h"
#include "Core/ECS/Custom/HealthComponent.h"
#include "Core/ECS/Custom/HealthIndicator.h"
#include "Core/ECS/Custom/PointComponent.h"
#include "Core/ECS/Custom/PointIndicator.h"

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
	auto player0 = std::make_shared<Engine::GameObject>("playerConsole", glm::vec2{ 100,100 });
	player0->AddComponent<Engine::TextureRendererComponent>("Resources/Sprites/space_ship.png");
	auto player0HealthComponent = player0->AddComponent<Engine::HealthComponent>();
	auto player0PointsComponent = player0->AddComponent<Engine::PointComponent>();

	// Player 2
	auto player1 = std::make_shared<Engine::GameObject>("playerRoot", glm::vec2{ 100,100 });
	player1->AddComponent<Engine::TextureRendererComponent>("Resources/Sprites/bug.png");
	auto player1HealthComponent = player1->AddComponent<Engine::HealthComponent>();
	auto player1PointsComponent = player1->AddComponent<Engine::PointComponent>();


	// health
	auto playerStatsRoot = std::make_shared<Engine::GameObject>("PlayerStats", glm::vec2{ 0, 0 });

	
	// player 0 stats (health and points) ------------------------------------------------------------------------------------------
	auto player0Stats = std::make_shared<Engine::GameObject>("Player0", glm::vec2{ 0,0 });
	auto player0Health = std::make_shared<Engine::GameObject>("Health", glm::vec2{0, 0});
	auto player0Points = std::make_shared<Engine::GameObject>("Points", glm::vec2{0, 50});

	// attach individual stats to root stat holder
	player0Stats->AttachChild(player0Health, false);
	player0Stats->AttachChild(player0Points, false);

	auto player0HealthIndicator = player0Health->AddComponent<Engine::HealthIndicator>(player0HealthComponent->GetHealth());
	auto player0PointsIndicator = player0Points->AddComponent<Engine::PointIndicator>(0);

	// Setup observers
	player0HealthComponent->RegisterObserver(player0HealthIndicator->GetObserver());
	player0PointsComponent->RegisterObserver(player0PointsIndicator->GetObserver());


	// player 1 stats (health and points) ------------------------------------------------------------------------------------------
	auto player1Stats = std::make_shared<Engine::GameObject>("Player1", glm::vec2{ 300,0 });
	auto player1Health = std::make_shared<Engine::GameObject>("Health", glm::vec2{0, 0});
	auto player1Points = std::make_shared<Engine::GameObject>("Points", glm::vec2{0, 50});

	// attach individual stats to root stat holder
	player1Stats->AttachChild(player1Health, false);
	player1Stats->AttachChild(player1Points, false);

	auto player1HealthIndicator = player1Health->AddComponent<Engine::HealthIndicator>(player1HealthComponent->GetHealth());
	auto player1PointsIndicator = player1Points->AddComponent<Engine::PointIndicator>(0);

	// Setup observers
	player1HealthComponent->RegisterObserver(player1HealthIndicator->GetObserver());
	player1PointsComponent->RegisterObserver(player1PointsIndicator->GetObserver());

	// ----------- ATTACH TO ROOT STATS ------------
	playerStatsRoot->AttachChild(player0Stats, false);
	playerStatsRoot->AttachChild(player1Stats, false);
	playerStatsRoot->SetShouldRenderImGui(true); // allow imgui

	scene.Add(player0);
	scene.Add(player1);
	scene.Add(playerStatsRoot);

	// Create controller
	InputManager::GetInstance().CreateController(0);

	// Console player
	InputManager::GetInstance().CreateConsoleCommand<Engine::ForwardCommand>(XINPUT_GAMEPAD_DPAD_UP, InputState::Hold, player0.get());
	InputManager::GetInstance().CreateConsoleCommand<Engine::DownCommand>(XINPUT_GAMEPAD_DPAD_DOWN, InputState::Hold, player0.get());
	InputManager::GetInstance().CreateConsoleCommand<Engine::LeftCommand>(XINPUT_GAMEPAD_DPAD_LEFT, InputState::Hold, player0.get());
	InputManager::GetInstance().CreateConsoleCommand<Engine::RightCommand>(XINPUT_GAMEPAD_DPAD_RIGHT, InputState::Hold, player0.get());
	InputManager::GetInstance().CreateConsoleCommand<Engine::DieCommand>(XINPUT_GAMEPAD_A, InputState::Press, player0.get());
	InputManager::GetInstance().CreateConsoleCommand<Engine::PointCommand>(XINPUT_GAMEPAD_B, InputState::Press, player0.get());

	// Desktop player
	InputManager::GetInstance().CreateDesktopCommand<Engine::ForwardCommand>(SDL_SCANCODE_UP, InputState::Hold, player1.get());
	InputManager::GetInstance().CreateDesktopCommand<Engine::DownCommand>(SDL_SCANCODE_DOWN, InputState::Hold, player1.get());
	InputManager::GetInstance().CreateDesktopCommand<Engine::LeftCommand>(SDL_SCANCODE_LEFT, InputState::Hold, player1.get());
	InputManager::GetInstance().CreateDesktopCommand<Engine::RightCommand>(SDL_SCANCODE_RIGHT, InputState::Hold, player1.get());
	InputManager::GetInstance().CreateDesktopCommand<Engine::DieCommand>(SDL_SCANCODE_F, InputState::Press, player1.get());
	InputManager::GetInstance().CreateDesktopCommand<Engine::PointCommand>(SDL_SCANCODE_P, InputState::Press, player1.get());

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