#include "DxLib.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle()
{
	m_fadeBright = 0;
	m_fadeSpeed = 0;
}

SceneTitle::~SceneTitle()
{

}


void SceneTitle::init()
{
	m_fadeBright = 0;
	m_fadeSpeed = 8;
}

void SceneTitle::end()
{
	SetDrawBright(225, 225, 225);
}

bool SceneTitle::update()
{
	m_fadeBright += m_fadeSpeed;
	if (m_fadeBright >= 225)
	{
		m_fadeBright = 225;
		m_fadeSpeed = 0;
	}
	if ((m_fadeBright <= 0) && (m_fadeBright < 0))
	{
		//�t�F�[�h�A�E�g���������玟�̃V�[����
		m_fadeBright = 0;
		return true;
	}



	// �L�[���͏���
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (m_fadeSpeed == 0)
	{
		if (padState & PAD_INPUT_1)
		{
			m_fadeSpeed = -8;
		}
	}
	return false;
}

void SceneTitle::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
	// �n�ʂ̕`��
	DrawString(0, 0, "SceneMain�̕\��", GetColor(255, 255, 255));
	
}