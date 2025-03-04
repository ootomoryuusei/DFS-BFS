#pragma once
#include "Engine/GameObject.h"
#include<vector>
#include<stack>
#include<map>
#include<queue>
#include<functional>

//テストシーンを管理するクラス
class TestScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TestScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

private:


	struct Edge {
		int to; //行先
		int cost; //コスト
	};

	using Graph = std::vector<std::vector<Edge>>;

	using Pair = std::pair<long long, int>;

	std::vector<int> route;

	void AllWall(int w, int h);
	void MakeMazeDigDug(int w, int h);
	void DigDug(int x, int y);
	void DrawMaze(int w, int h);
	void MakeWall(int w, int h);

	void BFS();

	void DijkstraMethod(const Graph& graph, std::vector<long long>& distances, int startIndex, int targetIndex, std::vector<int>& path);

};