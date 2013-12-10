#ifndef INPUT_H
#define INPUT_H

#include <glm/glm.hpp>

namespace KitKat
{
	class Input
	{
	public:
		Input();
		~Input();

		static void processPosition(int x, int y);
		static void processClick(bool click);

		static glm::vec2 getPosition();
		static bool isClick();

	private:

		static bool _click;
		static glm::vec2 _inputPos;
	};
}

#endif