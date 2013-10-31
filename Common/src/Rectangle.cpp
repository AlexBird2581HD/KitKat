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

bool Rectangle::Contains(Vector2 position)
{
	int Right = Left + Width;
	int Bottom = Top + Height; 

	if(position.x > Left && position.x < Right
		&& position.y > Top && position.y < Bottom)
	{
		return true;
	}

	return false;
}

bool Rectangle::Intersects(Rectangle rectangle)
{
	Vector2 leftTop, leftBottom, rightTop, rightBottom;

	// Top left corner
	leftTop.x = rectangle.Left;
	leftTop.y = rectangle.Top;

	// Bottom left corner
	leftBottom.x = rectangle.Left;
	leftBottom.y = rectangle.Top + rectangle.Height;

	// Top right corner
	rightTop.x = rectangle.Left + Width;
	rightTop.y = rectangle.Top;

	// Bottom right corner
	rightBottom.x = rectangle.Left + Width;
	rightBottom.y = rectangle.Top + rectangle.Height;

	// Use this keyword for clarity
	// If any corner is inside the rectangle they intersect
	if(this->Contains(leftTop) || this->Contains(leftBottom)
		|| this->Contains(rightTop) || this->Contains(rightBottom))
	{
		return true;
	}
 
	return false;
}