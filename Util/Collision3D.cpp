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

bool Collision3D::UpdateCheck(std::vector<VECTOR>pos1, std::vector<VECTOR>pos2)
{
	// 現在のポジション保存数の数を保存一時的に保存する
	int tempPos1 = m_pos1Num;
	int tempPos2 = m_pos2Num;

	// 配列が存在しない場合は以下の処理を行わない
	if (pos1.size() == 0)return false;
	if (pos2.size() == 0)return false;

	// 配列の数が変わっていない場合はカウントしない
	if (pos1.size() != m_tempMax1Num)m_pos1Num++;
	if (pos2.size() != m_tempMax2Num)m_pos2Num++;

	// pos2よりpos1の方が大きい場合
	if (pos1.size() > pos2.size())
	{
		// 最大値を固定
		if (m_pos1Num == pos1.size())
		{
			m_pos1Num = pos1.size();
		}
	}
	else if (pos1.size() < pos2.size())
	{
		// 最大値を固定
		if (m_pos2Num == pos2.size())
		{
			m_pos2Num = pos2.size();
		}
	}

	// 配列最大数を一時的に記録
	m_tempMax1Num = pos1.size();
	m_tempMax2Num = pos2.size();


	// 判定処理
	const VECTOR vec = VSub(pos1[m_pos1Num], pos2[m_pos2Num]);
	const float del = VSize(vec);
	if (del < 128 * 2 + 68)
	{
		return true;
	}

	return false;
}
