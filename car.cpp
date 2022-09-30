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

	// �W�����v��
	constexpr float kJumpAcc = -32.0f;

}


Car::Car()
{
	m_handle = -1;
	m_fieldY = 0.0f;
//	MoveType m_moveType;
	m_isRestart = 0;
	m_stopFrame = 0;
	m_isJump = 0;
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

	// �����̃o���G�[�V������I��
	int randNum = GetRand(99);

	if (randNum < 38)
	{
		m_moveType = kMoveTypeNormal;
	}
	else if (randNum < 38 + 30)
	{
		m_moveType = kMoveTypeStop;
	}
	else if (randNum < 38 + 30 + 30)
	{
		m_moveType = kMoveTypeJump;
	}
	else
	{
		m_moveType = kMoveTypeReturn;
	}
	// �f�o�b�O�p�ɋ��������߂�
//	m_moveType = kMoveTypeJump;

	// �����n�߂�܂ł̎��Ԃ�ݒ�  1�b����3�b�҂@60�t���[������180�t���[��
	m_waitFrame = GetRand(kwaitFrameMax - kwaitFrameMin) + kwaitFrameMin;

	// �ēo��t���O������
	m_isRestart = false;

	// �������ʕϐ���������
	m_stopFrame = 0;
	m_isJump = false;

}

void Car::update()
{
	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return;
	}

	switch (m_moveType)
	{
	case kMoveTypeNormal:
		updateNormal();
		break;

	case kMoveTypeStop:
		updateStop();
		break;

	case kMoveTypeJump:
		updateJump();
		break;

	case kMoveTypeReturn:
		updateReturn();
		break;
		
	default:
		updateNormal();
		break;

	}
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
	if ((m_pos.x < 400.0f) && (m_stopFrame < 30))
	{
		m_stopFrame++;
		return;
	}
	m_pos += m_vec;

	// ��ʊO�ɏo����I��
	if (m_pos.x < (0.0f - m_size.x))
	{
		m_isRestart = true;
	}
}

// �W�����v����
void Car::updateJump()
{
	m_pos += m_vec;

	if (m_pos.y > m_fieldY - m_size.y)
	{
		m_pos.y = m_fieldY - m_size.y;
	}

	if (!m_isJump && m_pos.x < 320.0f)
	{
		m_isJump = true;
		m_vec.y = -32.0f;
	}
	
	if (m_pos.x < (0.0f - m_size.x))
	{
		m_isRestart = true;
	}
	
}

// �r���ň����Ԃ�(�K������)
void Car::updateReturn()
{
	if ((m_pos.x < 360.0f) && (m_stopFrame < 60))
	{
		m_stopFrame++;
		if (m_stopFrame >= 60)
		{
			m_vec.x *= -1.0f;
		}
		return;
	}
	m_pos += m_vec;

	// ��ʊO�ɏo����I��
	if ((m_stopFrame >= 60) && (m_pos.x > Game::kScreenWidth))
	{
		m_isRestart = true;
	}
}