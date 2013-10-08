#include <KitKatMath/Rectangle.h>

using namespace KitKatMath;


Rectangle::Rectangle()
{
	Left = 0;
	Top = 0;
	Width = 0;
	Height = 0;
}

Rectangle::Rectangle(float left, float top, float width, float height)
{
	Left = left;
	Top = top;
	Width = width;
	Height = height;
}

Rectangle::Rectangle(Vector2 position, float width, float height)
{
	Left = position.x;
	Top = position.y;
	Width = width;
	Height = height;
}

Rectangle::Rectangle(Vector2 position, Vector2 size)
{
	Left = position.x;
	Top = position.y;
	Width = size.x;
	Height = size.y;
}

Rectangle::~Rectangle() { }

// Public

bool Rectangle::Intersects(Rectangle rectangle)
{
	return true;
}

bool Rectangle::Contains(Vector2 position)
{
	int Right = Left + Width;
	int Bottom = Top + Height; 

	if(position.x > Left && position.x < Right
		&& position.y > Top && position.y < Bottom)
		return true;

	return false;
}