#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	// �҂�����
	constexpr int kwaitFrameMin = 60;
	constexpr int kwaitFrameMax = 180;

	// �Ԃ̑��x
	constexpr float kSpeed = -24.0f;
}


Car::Car()
{
	m_handle = -1;
	m_fieldY = 0.0f;
	m_waitFrame = 0;
}

void Car::setGraphic(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_size.x, &m_size.y);
}

void Car::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = Game::kScreenWidth + 16.0f;
	m_pos.y = m_fieldY - m_size.y;

	m_vec.x = kSpeed;
	m_vec.y = 0.0f;

	// �����n�߂�܂ł̎��Ԃ�ݒ�  1�b����3�b�҂@60�t���[������180�t���[��
	m_waitFrame = GetRand(120) + 60;
}

void Car::update()
{
	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return;
	}
	m_pos += m_vec;		// �܂������i��
}

void Car::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	DrawFormatString(0, 0, GetColor(225, 225, 225), "wait:%d", m_waitFrame);
}

// private

// �܂������i��
void Car::updateNormal()
{
	m_pos += m_vec;	
}	

// �ꎞ��~�t�F�C���g
void Car::updateStop()
{

}

// �W�����v����
void Car::updateJump()
{

}

// �r���ň����Ԃ�(�K������)
void Car::updateReturn()
{

}