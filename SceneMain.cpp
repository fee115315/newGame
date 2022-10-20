#include "DxLib.h"
#include "SceneMain.h"
#include "ShotNormal.h"
#include "ShotFall.h"
#include "ShotP.h"
#include "Back.h"
#include "Enemy.h"
#include "Enemy_2.h"
#include "EnemyBase.h"

#include "Title.h"
#include "End.h"
#include "Clear.h"

#include <cassert>


namespace
{
	//ショットの発射間隔
	constexpr int kShotInterval = 16;
	// プレイヤーのサイズ
	constexpr int kPlayerGraphicSizeX = 40;
	constexpr int kPlayerGraphicSizeY = 40;
	// 敵のサイズ
	constexpr int kEnemyGraphicSizeX = 60;
	constexpr int kEnemyGraphicSizeY = 60;
	// 敵2のサイズ
	constexpr int kEnemyGraphic2SizeX = 60;
	constexpr int kEnemyGraphic2SizeY = 60;
	// ショットのサイズa
	constexpr int kShotGraphicSizeX = 16.0f;
	constexpr int kShotGraphicSizeY = 16.0f;
	//自分のライフ
	constexpr int playerLife = 30;
	//敵のライフ
	constexpr int enemyLife = 10;
	//敵２のライフ
	constexpr int enemy2Life =10;
}

SceneMain::SceneMain()
{
	m_hPlayerGraphic = -1;
	m_hShotGraphic = -1;
	m_hTestSound = -1;
	m_hbackGraphic = -1;
	m_life = playerLife;
	e_life = enemyLife;
	e2_life = enemy2Life;
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
	m_hbackGraphic = LoadGraph("data/ega.png");
	m_back.setHandle(m_hbackGraphic);
	//敵のロード
	m_hEnemyGraphic = LoadGraph("data/ana.png");
	m_enemy.setHandle(m_hEnemyGraphic);
	//敵のロード
	m_hEnemyGraphic2 = LoadGraph("data/ringo.png");
	m_enemy2.setHandle(m_hEnemyGraphic2);
	//敵の弾のロード
	m_hShotEnemyGraphic = LoadGraph("data/oringo.png");
	m_enemy.setShotHandle(m_hShotEnemyGraphic);
	//敵2の弾のロード
	m_hShotEnemyGraphic2 = LoadGraph("data/oringo.png");
	m_enemy2.setShotHandle(m_hShotEnemyGraphic2);
	//弾のロード
	m_hShotGraphic = LoadGraph("data/oringo.png");
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
TitleBase* SceneMain::update()
{
	if (Col_Shot())
	{
		m_life--;	//死亡時ライフを一つ減らす
		if (m_life == 0)
		{
			return (new End);
		}
	}
	if (Col_ShotE())
	{
		e_life--;	//死亡時ライフを一つ減らす
		if (e_life == 0)
		{
			return (new Clear);
		}
	}
	if (Col_ShotE2())
	{
		e2_life--;	//死亡時ライフを一つ減らす
		if (e2_life == 0)
		{
			return (new Clear);
		}
	}
	if (Col_Enemy())
	{
		m_life--;	//死亡時ライフを一つ減らす
		if (m_life == 0)
		{
			return (new End);
		}
	}
	if (Col_Enemy2())
	{
		m_life--;	//死亡時ライフを一つ減らす
		if (m_life == 0)
		{
			return (new End);
		}
	}
	int padstate = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padstate & PAD_INPUT_1)
	{
		PlaySoundMem(m_hTestSound, DX_PLAYTYPE_BACK, true);
	}

	
	m_player.update();
	m_enemy.update();
	m_enemy2.update();
	m_back.update();

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
	
	return this;
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
	//プレイヤーのライフを表示
	DrawFormatString(0, 0, GetColor(0, 0, 0), "自分のライフ:%d", m_life);
	//敵のライフを表示
	DrawFormatString(500, 0, GetColor(0, 0, 0), "林のライフ:%d", e_life);
	//敵２のライフを表示
	DrawFormatString(500, 60, GetColor(0, 0, 0), "米満のライフ:%d", e2_life);
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
		/*pShot->getPos();*/

		float shotLeft = pShot->getPos().x;
		float shotRight = pShot->getPos().x + kShotGraphicSizeX;
		float shotTop = pShot->getPos().y;
		float shotBottom = pShot->getPos().y + kShotGraphicSizeY;

		float playerLeft = m_player.getPos().x;
		float playerRight = m_player.getPos().x + kPlayerGraphicSizeX - 10;
		float playerTop = m_player.getPos().y;
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

bool SceneMain::Col_ShotE()
{
	m_enemy.getPos();


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

		float playerLeft = m_enemy.getPos().x + 15;
		float playerRight = m_enemy.getPos().x + kEnemyGraphicSizeX - 15;
		float playerTop = m_enemy.getPos().y - 21;
		float playerBottom = m_enemy.getPos().y + kEnemyGraphicSizeY + 21;

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

bool SceneMain::Col_ShotE2()
{
	m_enemy.getPos();


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

		float playerLeft = m_enemy2.getPos().x + 15;
		float playerRight = m_enemy2.getPos().x + kEnemyGraphic2SizeX - 15;
		float playerTop = m_enemy2.getPos().y -21;
		float playerBottom = m_enemy2.getPos().y + kEnemyGraphic2SizeX + 21;

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

		float playerLeft = m_player.getPos().x - 10;
		float playerRight = m_player.getPos().x + kPlayerGraphicSizeX -10;
		float playerTop = m_player.getPos().y - 10;
		float playerBottom = m_player.getPos().y + kPlayerGraphicSizeY -10;

		float enemyLeft = m_enemy.getPos().x + 15;
		float enemyRight = m_enemy.getPos().x + kEnemyGraphicSizeX - 15;
		float enemyTop = m_enemy.getPos().y - 21;
		float enemyBottom = m_enemy.getPos().y + kEnemyGraphicSizeY +21;

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

		float enemyLeft = m_enemy2.getPos().x + 15;
		float enemyRight = m_enemy2.getPos().x + kEnemyGraphicSizeX - 15;
		float enemyTop = m_enemy2.getPos().y -21;
		float enemyBottom = m_enemy2.getPos().y + kEnemyGraphicSizeY +21;

		if (playerLeft > enemyRight) return false;
		if (playerRight < enemyLeft) return false;
		if (playerTop > enemyBottom) return false;
		if (playerBottom < enemyTop) return false;

		return true;
	}

