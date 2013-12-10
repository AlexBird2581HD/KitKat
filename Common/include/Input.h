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

		void processPosition(int x, int y);
		void processClick(bool click);

		glm::vec2 getPosition();
		bool isClick();

	private:

		bool _click;
		glm::vec2 _inputPos;
	};
}

#endif