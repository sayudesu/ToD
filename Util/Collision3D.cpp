#include "Collision3D.h"

bool Collision3D::UpdateCheck(VECTOR pos1, VECTOR pos2,float radius1,float radius2)
{
	// ”»’èˆ—
	const VECTOR vec = VSub(pos1, pos2);
	const float del = VSize(vec);

	if (del < radius1 + radius2)
	{
		return true;
	}

	return false;
}
