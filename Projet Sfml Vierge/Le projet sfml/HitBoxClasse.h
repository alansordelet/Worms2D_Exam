#pragma once
#include "tools.h"



class HitBoxClasse
{

public:

	HitBoxClasse();
	~HitBoxClasse();


	static inline bool pointRect(Vector2f _PosPoint, Sprite _Sprite) {
		
		// is the point inside the rectangle's bounds?

		if (_PosPoint.x >= _Sprite.getGlobalBounds().left &&        // right of the left edge AND
			_PosPoint.x <= _Sprite.getGlobalBounds().left + _Sprite.getGlobalBounds().width &&   // left of the right edge AND
			_PosPoint.y >= _Sprite.getGlobalBounds().top &&        // below the top AND
			_PosPoint.y <= _Sprite.getGlobalBounds().top + _Sprite.getGlobalBounds().height) {   // above the bottom
			return true;
		}
		return false;
	};

	static inline bool circleRect(Vector2f _Pos, float radius,Vector2f _PositionSpri,Sprite _SpriteSize ) {

		// temporary variables to set edges for testing


		float cx = _Pos.x;
		float cy = _Pos.y;
		float rx = _PositionSpri.x;
		float ry = _PositionSpri.y;
		float rw = _SpriteSize.getGlobalBounds().width;
		float rh = _SpriteSize.getGlobalBounds().height;



		float testX = cx;
		float testY = cy;

		// which edge is closest?
		if (cx < rx)         testX = rx;      // test left edge
		else if (cx > rx + rw) testX = rx + rw;   // right edge
		if (cy < ry)         testY = ry;      // top edge
		else if (cy > ry + rh) testY = ry + rh;   // bottom edge

		// get distance from closest edges
		float distX = cx - testX;
		float distY = cy - testY;
		float distance = sqrt((distX * distX) + (distY * distY));

		// if the distance is less than the radius, collision!
		if (distance <= radius) {
			return true;
		}
		return false;
	}


	static inline bool circleCircle(Vector2f Pos1, float c1r, Vector2f Pos2, float c2r) {

		// get distance between the circle's centers
		// use the Pythagorean Theorem to compute the distance
		float distX = Pos1.x - Pos2.x;
		float distY = Pos1.y - Pos2.y;
		float distance = sqrt((distX * distX) + (distY * distY));

		// if the distance is less than the sum of the circle's
		// radii, the circles are touching!
		if (distance <= c1r + c2r) {
			return true;
		}
		return false;
	}




	static inline bool rectRect( Sprite _sprite, Vector2f _posSprite, float r2w, float r2h) {
		float r1x = _sprite.getGlobalBounds().left+6;
		float r1y = _sprite.getGlobalBounds().top+11;
		float r1w = _sprite.getGlobalBounds().width -12;
		float r1h = _sprite.getGlobalBounds().height-11;

		float r2x =_posSprite.x;
		float r2y = _posSprite.y;
		// are the sides of one rectangle touching the other?

		if (r1x + r1w >= r2x &&    // r1 right edge past r2 left
			r1x <= r2x + r2w &&    // r1 left edge past r2 right
			r1y + r1h >= r2y &&    // r1 top edge past r2 bottom
			r1y <= r2y + r2h) {    // r1 bottom edge past r2 top
			return true;
		}
		return false;
	}

};
