#pragma once
#include "Vector2D.h"

class Rectangle {
	public:
		Rectangle();
		Rectangle(Vector2D minPosition, Vector2D size);	
		Rectangle(float minX, float minY, float sizeX, float sizeY);

		const Vector2D& GetMinPosition() const;
		const Vector2D& GetSize() const;
		void SetMinPosition(Vector2D position);
		void SetSize(Vector2D size);
		
		Vector2D GetMaxPosition() const;
		Vector2D GetCenterPosition() const;
		bool Contains(const Vector2D& point) const;
		static Rectangle ConstructMinMax(Vector2D minPosition, Vector2D maxPosition);
		
	private:
		Vector2D minPosition, size;
};