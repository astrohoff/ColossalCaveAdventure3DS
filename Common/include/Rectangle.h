#pragma once
#include "Vector2D.h"

class Rectangle {
	public:
		Vector2D minPosition, size;

		Rectangle();
		Rectangle(Vector2D minPosition, Vector2D size);	
		Rectangle(float minX, float minY, float sizeX, float sizeY);

		void SetPosition(const Vector2D& position);
		Vector2D GetMaxPosition() const;
		Vector2D GetCenter() const;
		// Width/height.
		float GetAspectRatio() const;
		bool Contains(const Vector2D& point) const;
		
		Rectangle GetPaddedRect(const Vector2D& padding) const;
		void ApplyAspectRatio(float newAspect, bool shrink);
};