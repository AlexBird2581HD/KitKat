#include "Mathlibrary.h"
#include <cmath>
#define PI 3.14159265358979323846264

namespace KitKat
{

Vector2::Vector2()
: x(0), y(0)
{	
}

Vector2::Vector2(float X, float Y)
	: x(X), y(Y)
{			
}

Vector2::~Vector2(){}
 
float Vector2::getLength()
{           
	return sqrt(pow(x,2) + pow(y,2));
}

float Vector2::getAngle()
{
	if (x == 0)
	{
		if (y > 0)
			return 90;
		return 270;
    }
	else
    {
		float angle = float(atan(y/x)*(180.0f/PI));
 
		if (x < 0)
			angle += 180;
 
		else if (angle < 0)
			angle += 360;
 
		return angle;
    }
}
 

Rectangle::Rectangle()
{
	left = 0;
	top = 0;
	width = 0;
	height = 0;
}
Rectangle::Rectangle(float Left, float Top, float Width, float Height)
{
	left = Left;
	top = Top;
	width = Width;
	height = Height;
}
Rectangle::Rectangle(Vector2 Position, float Width, float Height)
{
	left = Position.x;
	top = Position.y;
	width = Width;
	height = Height;
}
Rectangle::Rectangle(Vector2 Position, Vector2 Size)
{
	left = Position.x;
	top = Position.y;
	width = Size.x;
	height = Size.y;
}
                         
Rectangle::~Rectangle()
{
}


// Operators - vector

Vector2& Vector2::operator +=(const Vector2& RightVal)
{
	this->x += RightVal.x;
	this->y += RightVal.y;
	return *this;
}
Vector2& Vector2::operator -=(const Vector2& RightVal)
{
	this->x -= RightVal.x;
	this->y -= RightVal.y;
	return *this;
}

Vector2& Vector2::operator *=(const float& RightVal)
{
	this->x *= RightVal;
	this->x *= RightVal;
	return *this;
}

Vector2& Vector2::operator /=(const float& RightVal)
{
	this->x /= RightVal;
	this->y /= RightVal;
	return *this;
}

Vector2 Vector2::operator +(const Vector2& RightVal)
{
	return Vector2(this->x + RightVal.x, this->y + RightVal.y);
}

Vector2 Vector2::operator -(const Vector2& RightVal)
{
	return Vector2(this->x - RightVal.x, this->y - RightVal.y);
}

Vector2 Vector2::operator -()
{
	return Vector2(-this->x, -this->y);
}

Vector2 Vector2::operator *(const float& RightVal)
{
	return Vector2(this->x * RightVal, this->y * RightVal);
}

Vector2 Vector2::operator /(const float& RightVal)
{
	return Vector2(this->x / RightVal, this->y / RightVal);
}

Vector2 operator *(const float& LeftVal, const Vector2& RightVal)
{
	return Vector2(LeftVal * RightVal.x, LeftVal * RightVal.y);
}

bool Vector2::operator ==(const Vector2& RightVal)
{
	if (this->x == RightVal.x && this->y == RightVal.y)
		return true;
	return false;
}

bool Vector2::operator !=(const Vector2& RightVal)
{
	return !(*this == RightVal);
}

}