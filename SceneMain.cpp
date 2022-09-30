#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"

namespace
{
	// ínñ ÇÃçÇÇ≥
	constexpr int kFieldY = Game::kScreenHeight - 64;
}

SceneMain::SceneMain()
{
	m_hPlayer = -1;
	m_hCar = -1;
}

SceneMain::~SceneMain()
{

}

void SceneMain::init()
{

	m_hPlayer = LoadGraph("data/player.png");
	m_hCar = LoadGraph("data/car.png");

	Player player;
	player.setGraphic(m_hPlayer);
	player.setup(kFieldY);

	Car car;
	car.setGraphic(m_hCar);
	car.setup(kFieldY);

}

void SceneMain::end()
{

	DeleteGraph(m_hPlayer);
	DeleteGraph(m_hCar);

}

bool SceneMain::update()
{
	m_player.update();
	m_car.update();
	// ìñÇΩÇËîªíË
	if (m_player.isCol(m_car))
	{
		m_player.setDead(true);
	}

	return false;
}

void SceneMain::draw()
{

	// ínñ ÇÃï`âÊ
	DrawLine(0, kFieldY, Game::kScreenWidth, kFieldY, GetColor(255, 255, 255));
	m_player.draw();
	m_car.draw();
}