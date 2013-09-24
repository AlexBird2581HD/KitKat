#ifndef MATH_H
#define MATH_H

namespace KitKat
{
class Vector2
{
public:
	Vector2();
	Vector2(float X, float Y);
	~Vector2();

	float getLength();
	float getAngle();
	float x,y;

	Vector2& operator +=(const Vector2& RightVal);
    Vector2& operator -=(const Vector2& RightVal);

	Vector2& operator *=(const float& RightVal);
	Vector2& operator /=(const float& RightVal);

    Vector2 operator +(const Vector2& RightVal);
    Vector2 operator -(const Vector2& RightVal);
	Vector2 operator -(); 
 
	Vector2 operator *(const float& RightVal);
	Vector2 operator /(const float& RightVal);
	// Needs leftVal
    friend Vector2 operator *(const float& LeftVal, const Vector2& RightVal);

    bool operator ==(const Vector2& RightVal);
    bool operator !=(const Vector2& RightVal);
};

class Rectangle
{
public:

	Rectangle();
	Rectangle(float Left, float Top, float Width, float Height);
	Rectangle(Vector2 Position, float Width, float Height);
	Rectangle(Vector2 Position, Vector2 Size);
		
		
	bool Intersects(Rectangle rectangle);
	bool Contains(Vector2 Position);
	~Rectangle();
	float width, height, left, top;

private:


};
}

#endif