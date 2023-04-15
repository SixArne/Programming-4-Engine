#ifndef DIE_COMMAND_H
#define DIE_COMMAND_H

#include "Command.h"

namespace Engine
{
	class DieCommand :public Command
	{
	public:
		DieCommand(GameObject* gobj) : Command{ gobj } {};
		// Inherited via Command
		virtual void Execute() override;
	};
}

#endif // !JUMP_COMMAND_H
