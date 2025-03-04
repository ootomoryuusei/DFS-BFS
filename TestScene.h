#pragma once
#include "Engine/GameObject.h"
#include<vector>
#include<stack>
#include<map>
#include<queue>
#include<functional>

//�e�X�g�V�[�����Ǘ�����N���X
class TestScene : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TestScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

private:


	struct Edge {
		int to; //�s��
		int cost; //�R�X�g
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