#include "pch.h"

#include "SceneManager.h"
#include "Scenes/Scene.h"

void Engine::SceneManager::Init()
{
	for (auto& scene : m_scenes)
	{
		scene->Init();
	}
}

void Engine::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void Engine::SceneManager::FixedUpdate(float fdt)
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(fdt);
	}
}

void Engine::SceneManager::LateUpdate()
{
	for (const auto& scene : m_scenes)
	{
		scene->LateUpdate();
	}
}

void Engine::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void Engine::SceneManager::OnImGui()
{
	for (const auto& scene : m_scenes)
	{
		scene->OnImGui();
	}
}

void Engine::SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	m_scenes.push_back(scene);
}

Engine::Scene& Engine::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
