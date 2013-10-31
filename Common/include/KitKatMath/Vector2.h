#ifndef VECTOR2_H
#define VECTOR2_H

namespace KitKatMath
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


		// Operators
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
}

#endif