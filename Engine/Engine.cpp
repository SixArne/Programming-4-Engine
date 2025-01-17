#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


#include "Engine.h"
#include "Core/Input/InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Core/Time.h"
#include "Core/Log.h"

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
		printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
			version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

Engine::Engine::Engine(const std::string& dataPath)
{
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

Engine::Engine::~Engine()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void Engine::Engine::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	bool doContinue = true;

	// Validate all game assets dependencies and setup
	sceneManager.Init();

	const float fixedTimeStepSec{ 0.02f };
	const float desiredFPS{ 144.f };
	const int frameTimeMs{ 1000 / (int)desiredFPS };
	float lag = 0.0f;

	auto lastTime = std::chrono::high_resolution_clock::now();
	while (doContinue)
	{

		// Delta time related stuff
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const auto deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - lastTime).count();

		lastTime = currentTime;
		lag += deltaTime;

		doContinue = input.ProcessInput();
		while (lag >= fixedTimeStepSec)
		{
			sceneManager.FixedUpdate(fixedTimeStepSec);
			lag -= fixedTimeStepSec;
		}

		sceneManager.Update();

		renderer.Render();
		renderer.RenderImGui(sceneManager);

		sceneManager.LateUpdate();

		TIME.Update(static_cast<float>(deltaTime));

		const auto sleeptime = currentTime + std::chrono::milliseconds(frameTimeMs) - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleeptime);
	}
}