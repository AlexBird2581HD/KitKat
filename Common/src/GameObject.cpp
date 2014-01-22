#include <GameObject.h>
#include <Debug.h>

using namespace KitKat;

GameObject::GameObject(int x, int y, float w, float h)
	: Quad(x, y, w, h)
{
}

GameObject::~GameObject()
{
}

void GameObject::Update(float dt)
{
	pos += velocity * dt;
	//move(pos.x, pos.y);
	LOGI("X: %f, Y: %f\n", pos.x, pos.y);
}

void GameObject::SetVelocity(glm::vec2 vel)
{
	velocity = vel;
}
