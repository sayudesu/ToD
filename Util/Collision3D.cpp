#include "Collision3D.h"

Collision3D::Collision3D():
	m_pos1Num(-1),
	m_pos2Num(-1),
	m_tempMax1Num(0),
	m_tempMax2Num(0)
{
}

Collision3D::~Collision3D()
{
	
}

bool Collision3D::UpdateCheck(VECTOR pos1, VECTOR pos2,float radius1,float radius2)
{
	// îªíËèàóù
	const VECTOR vec = VSub(pos1, pos2);
	const float del = VSize(vec);

	if (del < radius1 + radius2)
	{
		return true;
	}

	return false;
}
