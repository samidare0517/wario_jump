#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	// 待ち時間
	constexpr int kwaitFrameMin = 60;
	constexpr int kwaitFrameMax = 180;

	// 車の速度
	constexpr float kSpeed = -24.0f;

	// ジャンプ力
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

	// 動きのバリエーションを選択
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
	// デバッグ用に挙動を決める
//	m_moveType = kMoveTypeJump;

	// 動き始めるまでの時間を設定  1秒から3秒待つ　60フレームから180フレーム
	m_waitFrame = GetRand(kwaitFrameMax - kwaitFrameMin) + kwaitFrameMin;

	// 再登場フラグ初期化
	m_isRestart = false;

	// 名挙動別変数を初期化
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

// まっすぐ進む
void Car::updateNormal()
{
	m_pos += m_vec;	
}	

// 一時停止フェイント
void Car::updateStop()
{
	if ((m_pos.x < 400.0f) && (m_stopFrame < 30))
	{
		m_stopFrame++;
		return;
	}
	m_pos += m_vec;

	// 画面外に出たら終了
	if (m_pos.x < (0.0f - m_size.x))
	{
		m_isRestart = true;
	}
}

// ジャンプする
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

// 途中で引き返す(必ず成功)
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

	// 画面外に出たら終了
	if ((m_stopFrame >= 60) && (m_pos.x > Game::kScreenWidth))
	{
		m_isRestart = true;
	}
}