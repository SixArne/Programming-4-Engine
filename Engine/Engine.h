#ifndef ENGINE_H
#define ENGINE_H

#include "pch.h"

namespace Engine
{
	class Engine
	{
	public:
		explicit Engine(const std::string& dataPath);
		~Engine();
		void Run(const std::function<void()>& load);

		Engine(const Engine& other) = delete;
		Engine(Engine&& other) = delete;
		Engine& operator=(const Engine& other) = delete;
		Engine& operator=(Engine&& other) = delete;
	};
}

#endif // !ENGINE_H