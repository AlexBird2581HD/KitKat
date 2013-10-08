#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <KitKatMath/Vector2.h>

namespace KitKatMath
{
	class Rectangle
	{
	public:

		Rectangle();
		Rectangle(float left, float top, float width, float height);
		Rectangle(Vector2 position, float width, float height);
		Rectangle(Vector2 position, Vector2 size);
		~Rectangle();
		
		float Width, Height, Left, Top;
		
		bool Intersects(Rectangle rectangle);
		bool Contains(Vector2 position);
	private:


	};
}
#endif