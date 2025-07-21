#include "GameScene.h"
#include"../SceneManager.h"

#include "../../Factory/Factory.h"

#include "../../GameObject/GameObject.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::GetInstance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
}

void GameScene::Init()
{

}