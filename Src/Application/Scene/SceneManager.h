#pragma once
#include "../Utility/SingletonBase.h"

class BaseScene;

class SceneManager : public SingletonBase<SceneManager>
{
public :

	// シーン情報
	enum class SceneType
	{
		Title,
		Game,
	};

	// マネージャーの初期化
	// インスタンス生成(アプリ起動)時にコンストラクタで自動実行
	void Init()
	{
		// 開始シーンに切り替え
		ChangeScene(m_currentSceneType);
	}

	void PreUpdate ();
	void Update    ();
	void PostUpdate();

	void PreDraw   ();
	void Draw      ();
	void DrawSprite();
	void DrawDebug ();

	std::weak_ptr<BaseScene> GetCurrentScene() { return m_currentScene; }

	// 次のシーンをセット (次のフレームから切り替わる)
	void SetNextScene(SceneType _nextScene)
	{
		m_nextSceneType = _nextScene;
	}

	// 現在のシーンのオブジェクトリストを取得
	const std::list<std::shared_ptr<GameObject>>& GetGameObjectList();

	// 現在のシーンにオブジェクトを追加
	void AddGameObject(const std::shared_ptr<GameObject>& GameObject);

private:

	// シーン切り替え関数
	void ChangeScene(SceneType _sceneType);

	// 現在のシーンのインスタンスを保持しているポインタ
	std::shared_ptr<BaseScene> m_currentScene = nullptr;

	// 現在のシーンの種類を保持している変数
	SceneType m_currentSceneType = SceneType::Game;
	
	// 次のシーンの種類を保持している変数
	SceneType m_nextSceneType = m_currentSceneType;

	// ==============================
	// "Singleton"
	// ==============================
	friend class SingletonBase;

	SceneManager ()          = default;
	~SceneManager() override = default;
};
