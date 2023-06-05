#pragma once
#include "SceneManager.h"

namespace Engine
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		explicit Scene(const std::string& name);
		void Add(std::shared_ptr<GameObject> object, bool isPersistant = false);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();
		void ClearPersistantObjects();

		void Init();
		void Update();
		void FixedUpdate(float fdt);
		void LateUpdate();
		void Render() const;
		void OnLoad();
		void OnUnload();
		virtual void OnImGui();

		const std::string& GetName() const { return m_name; }

		std::shared_ptr<GameObject> FindByName(const std::string& name) const;
		const std::vector<std::shared_ptr<GameObject>> GetPersistantObjects();

		void Instantiate(std::shared_ptr<GameObject> object, bool isPersistant = false);
		bool IsInitialized();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	protected:
		std::string m_name;
		std::vector<std::shared_ptr<GameObject>> m_objects{};
		std::vector<std::shared_ptr<GameObject>> m_objectsToDestroy{};
		std::vector<std::shared_ptr<GameObject>> m_PersistantObjects{};

		bool m_IsInitialized{false};

		static unsigned int m_idCounter;
	};

}
