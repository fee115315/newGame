#include "DxLib.h"
#include "SceneMain.h"
#include "ShotBound.h"
#include "ShotNormal.h"
#include "ShotFall.h"
#include "ShotP.h"
#include "Back.h"
#include "Enemy.h"
#include "Enemy_2.h"
#include "EnemyBase.h"

#include <cassert>


namespace
{
	//ショットの発射間隔
	constexpr int kShotInterval = 16;
	// プレイヤーのサイズ
	constexpr int kPlayerGraphicSizeX = 32;
	constexpr int kPlayerGraphicSizeY = 32;
	// 敵のサイズ
	constexpr int kEnemyGraphicSizeX = 32;
	constexpr int kEnemyGraphicSizeY = 32;
	// 敵のサイズ
	constexpr int kEnemyGraphic2SizeX = 32;
	constexpr int kEnemyGraphic2SizeY = 32;
	// ショットのサイズ
	constexpr int kShotGraphicSizeX = 16.0f;
	constexpr int kShotGraphicSizeY = 16.0f;
	//自分のライフ
	constexpr int playerLife = 10;
}

SceneMain::SceneMain()
{
	m_hPlayerGraphic = -1;
	m_hShotGraphic = -1;
	m_hTestSound = -1;
	m_hbackGraphic = -1;
	m_life = playerLife;
	m_hitInvi = 0;
}
SceneMain::~SceneMain()
{

}

// 初期化
void SceneMain::init()
{
	//グラフィックのロード
	m_hPlayerGraphic = LoadGraph("data/player.bmp");
	m_player.setHandle(m_hPlayerGraphic);
	//背景のロード
	m_hbackGraphic = LoadGraph("data/ino.png");
	m_back.setHandle(m_hbackGraphic);
	//敵のロード
	m_hEnemyGraphic = LoadGraph("data/ana.png");
	m_enemy.setHandle(m_hEnemyGraphic);
	//敵のロード
	m_hEnemyGraphic2 = LoadGraph("data/ana.png");
	m_enemy2.setHandle(m_hEnemyGraphic2);
	//敵の弾のロード
	m_hShotEnemyGraphic = LoadGraph("data/shot.bmp");
	m_enemy.setShotHandle(m_hShotEnemyGraphic);
	//敵の弾のロード
	m_hShotEnemyGraphic2 = LoadGraph("data/shot.bmp");
	m_enemy2.setShotHandle(m_hShotEnemyGraphic2);
	//弾のロード
	m_hShotGraphic = LoadGraph("data/shot.bmp");
	//サウンドのロード
	LoadSoundMem("music/cursor7.mp3");

	m_player.init();
	m_player.setMain(this);
	m_enemy.init();
	m_enemy.setMain(this);
	m_enemy2.init();
	m_enemy2.setMain(this);
}

// 終了処理
void SceneMain::end()
{
	//グラフィックアンロード
	DeleteGraph(m_hPlayerGraphic);
	DeleteGraph(m_hShotGraphic);
	DeleteGraph(m_hbackGraphic);
	DeleteGraph(m_hEnemyGraphic);
	DeleteGraph(m_hShotEnemyGraphic);
	DeleteGraph(m_hEnemyGraphic2);
	DeleteGraph(m_hShotEnemyGraphic2);
	//サウンドアンロード
	DeleteSoundMem(m_hTestSound);
	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);

		delete pShot;
		pShot = nullptr;
	}
}

// 毎フレームの処理
void SceneMain::update()
{
	if (Col_Shot())
	{
		DxLib_End();
	}
	if (Col_Enemy())
	{
		DxLib_End();
	}
	if (Col_Enemy2())
	{
		DxLib_End();
	}
	int padstate = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padstate & PAD_INPUT_1)
	{
		PlaySoundMem(m_hTestSound, DX_PLAYTYPE_BACK, true);
	}

	
	m_player.update();
	m_enemy.update();
	m_enemy2.update();

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);

		if (!pShot)		//nullの場合処理しない
		{
			it++;
			continue;
		}

		pShot->update();
		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			//vectorの要素削除
			it = m_pShotVt.erase(it);
			continue;
		}
		it++;
	}
	m_back.update();
	
}

// 毎フレームの描画
void SceneMain::draw()
{
	m_back.draw();
	m_player.draw();
	m_enemy.draw();
	m_enemy2.draw();

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->draw();
	}

	//現在存在している弾の数を表示
	DrawFormatString(0, 0, GetColor(255, 255, 255), "弾の数:%d", m_pShotVt.size());
}

bool SceneMain::createShotNormal(Vec2 pos,int vect)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos,vect);
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotFall(Vec2 pos, int vect)
{
	ShotFall* pShot = new ShotFall;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos,vect);
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotBound(Vec2 pos, int vect)
{
	ShotBound* pShot = new ShotBound;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos,vect);
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotP(Vec2 pos)
{
	ShotP* pShot = new ShotP;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::Col_Shot()
{
	m_player.getPos();

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);
		assert(pShot);
		pShot->getPos();

		float shotLeft = pShot->getPos().x;
		float shotRight = pShot->getPos().x + kShotGraphicSizeX;
		float shotTop = pShot->getPos().y;
		float shotBottom = pShot->getPos().y + kShotGraphicSizeY;

		float playerLeft = m_player.getPos().x + 10;
		float playerRight = m_player.getPos().x + kPlayerGraphicSizeX - 10;
		float playerTop = m_player.getPos().y + 10;
		float playerBottom = m_player.getPos().y + kPlayerGraphicSizeY - 10;

		if (playerLeft > shotRight)
		{
			it++;
			continue;
		}
		if (playerRight < shotLeft)
		{
			it++;
			continue;
		}
		if (playerTop > shotBottom)
		{
			it++;
			continue;
		}
		if (playerBottom < shotTop)
		{
			it++;
			continue;
		}
		return true;
	}
	return false;
}



	bool SceneMain::Col_Enemy()
	{
		m_player.getPos();
		m_enemy.getPos();

		float playerLeft = m_player.getPos().x + 10;
		float playerRight = m_player.getPos().x + kPlayerGraphicSizeX - 10;
		float playerTop = m_player.getPos().y + 10;
		float playerBottom = m_player.getPos().y + kPlayerGraphicSizeY - 10;

		float enemyLeft = m_enemy.getPos().x + 10;
		float enemyRight = m_enemy.getPos().x + kEnemyGraphicSizeX - 10;
		float enemyTop = m_enemy.getPos().y + 10;
		float enemyBottom = m_enemy.getPos().y + kEnemyGraphicSizeY - 10;

		if (playerLeft > enemyRight) return false;
		if (playerRight < enemyLeft) return false;
		if (playerTop > enemyBottom) return false;
		if (playerBottom < enemyTop) return false;

		return true;
	}

	bool SceneMain::Col_Enemy2()
	{
		m_player.getPos();
		m_enemy2.getPos();

		float playerLeft = m_player.getPos().x + 10;
		float playerRight = m_player.getPos().x + kPlayerGraphicSizeX - 10;
		float playerTop = m_player.getPos().y + 10;
		float playerBottom = m_player.getPos().y + kPlayerGraphicSizeY - 10;

		float enemyLeft = m_enemy2.getPos().x + 10;
		float enemyRight = m_enemy2.getPos().x + kEnemyGraphicSizeX - 10;
		float enemyTop = m_enemy2.getPos().y + 10;
		float enemyBottom = m_enemy2.getPos().y + kEnemyGraphicSizeY - 10;

		if (playerLeft > enemyRight) return false;
		if (playerRight < enemyLeft) return false;
		if (playerTop > enemyBottom) return false;
		if (playerBottom < enemyTop) return false;

		return true;
	}

