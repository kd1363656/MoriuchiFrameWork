#pragma once

class BaseScene
{
public :

	BaseScene         () = default;
	virtual ~BaseScene() = default;

	virtual void Init();

	void PreUpdate ();
	void Update    ();
	void PostUpdate();

	void PreDraw   ();
	void Draw      ();
	void DrawSprite();
	void DrawDebug ();

	// オブジェクトリストを取得
	const std::list<std::shared_ptr<KdGameObject>>& GetGameObjectList()
	{
		return m_gameObjectList;
	}
	
	// オブジェクトリストに追加
	void AddGameObject(const std::shared_ptr<KdGameObject>& _obj)
	{
		m_gameObjectList.push_back(_obj);
	}

protected:

	// 継承先シーンで必要ならオーバーライドする
	virtual void Event();
	
	// 全オブジェクトのアドレスをリストで管理
	std::list<std::shared_ptr<KdGameObject>> m_gameObjectList;
};
