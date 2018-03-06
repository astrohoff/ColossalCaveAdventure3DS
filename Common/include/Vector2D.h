#pragma once
class Vector2D {
	public:
		float x, y;
		
		Vector2D();
		Vector2D(float x, float y);

		Vector2D operator+(const Vector2D& v) const;
		Vector2D& operator+=(const Vector2D& v);
		Vector2D operator-(const Vector2D& v) const;
		Vector2D& operator-=(const Vector2D& v);
		Vector2D operator/(float f) const;
		Vector2D& operator/=(float f);
		Vector2D operator*(float f) const;
		Vector2D& operator*=(float f);
		bool operator==(const Vector2D& v) const;
		bool operator!=(const Vector2D& v) const;	
};