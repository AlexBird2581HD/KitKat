#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Quad.h>
#include <glm/glm.hpp>

namespace KitKat
{
	class GameObject : public Quad
	{
	public:
		GameObject(int x, int y, float w, float h);
		~GameObject();

		void Update(float dt);

		void SetVelocity(glm::vec2 vel);

	private:
		glm::vec2 velocity;
	};
}

#endif