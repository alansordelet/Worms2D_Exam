#pragma once
#include "tools.h"
#include "HitBoxClasse.h"
#include <List>

static class MathBougeage
{
public:
	MathBougeage() {};
	~MathBougeage() {};




	inline static Vector2f Norm(float _Speed, float _Angle) {


		return Vector2f(_Speed * sin(_Angle * 3.1415 / 180.0f), _Speed * cos(_Angle * 3.1415 / 180.0f));
	}

	inline static Vector2f FollowEnnemis(Vector2f _PosSuivie, Vector2f _PosSuiveur, int _vitess) {

		Vector2f Vector{ _PosSuivie.x - _PosSuiveur.x,_PosSuivie.y - _PosSuiveur.y };

		float norm = sqrt(Vector.x * Vector.x + Vector.y * Vector.y);


		return Vector2f(_vitess * (Vector.x / norm), _vitess * (Vector.y / norm));
	}


	inline static float AbgleEntre2point(int p1x, int p1y, int p2x, int p2y)
	{
		//Make point1 the origin, make point2 relative to the origin so we do point1 - point1, and point2-point1,
		//since we dont need point1 for the equation to work, the equation works correctly with the origin 0,0.
		int deltaY = p2y - p1y;
		int deltaX = p2x - p1x; //Vector 2 is now relative to origin, the angle is the same, we have just transformed it to use the origin.

		float angleInDegrees = atan2(deltaY, deltaX) * 180 / 3.141;

		angleInDegrees *= -1; // Y axis is inverted in computer windows, Y goes down, so invert the angle.

		//Angle returned as:
		//                      90
		//            135                45
		//
		//       180          Origin           0
		//
		//           -135                -45
		//
		//                     -90


		// returned angle can now be used in the c++ window function used in text angle alignment. ie plf->lfEscapement = angle*10;
		return angleInDegrees;
	}

private:

};



