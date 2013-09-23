#ifndef MATH_H
#define MATH_H

namespace KitKat
{
	class Vector
	{
	public:
		Vector();
		Vector(float X, float Y);
		~Vector();

		float getLength();
		float getAngle();
		float x,y;
	private:
	
	};

			Vector operator -(const Vector& RightVal);
 
            Vector operator +(const Vector& LeftVal,const Vector& RightVal);
            Vector operator -(const Vector& LeftVal,const Vector& RightVal);
 
            Vector operator +=(Vector& LeftVal,const Vector& RightVal);
            Vector operator -=(Vector& LeftVal,const Vector& RightVal);
 
            Vector operator /(const Vector& LeftVal,const float& RightVal);
            Vector operator /=(Vector& LeftVal,const float& RightVal);
 
            bool operator ==(const Vector& LeftVal,const Vector& RightVal);
            bool operator !=(const Vector& LeftVal,const Vector& RightVal);
 
            Vector operator *(const Vector& LeftVal, const float& RightVal);
            Vector operator *(const float& LeftVal, const Vector& RightVal);
 
            const Vector operator *=(Vector& LeftVal, const float& RightVal);

class Rectangle
{
	public:

		Rectangle();
		Rectangle(float Left, float Top, float Width, float Height);
		Rectangle(Vector Position, float Width, float Height);
		Rectangle(Vector Position, Vector Size);
		
		
		bool intersects(Rectangle rectangle);
		bool contains(Vector Position);
		~Rectangle();
		float width, height, left, top;

	private:


};


}

#endif