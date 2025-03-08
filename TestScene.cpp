#include "TestScene.h"
#include "ImGui/imgui.h"
#include "Engine/SceneManager.h"
#include"Stage.h"
#include"Player.h"
#include"Enemy.h"


//namespace {
//	struct BOX {
//		int X1, X2, Y1, Y2;
//		int State;
//		int Weight;
//		int num;
//	};
//
//	enum BOXSTATE {
//		ROAD,
//		WALL,
//		START,
//		GOAL,
//		BAR,
//		MAX
//	};
//	const int width = 21;
//	const int height = 17;
//
//	BOX Map[height][width];
//
//	int bSize = 35;
//
//	int posX1 = 300;
//	int posX2 = posX1 + bSize;
//	int posY1 = 100;
//    int posY2 = posY1 + bSize;
//
//	int num = 0;
//
//     struct Point {
//		int x, y;
//	};
//
//	 const Point Start = { 1,1 };
//	 const Point Goal = { width - 2,height - 2 };
//	 std::stack<Point> prStack;
//
//	 int MapDataForSearch[height][width];
//
//	 constexpr long long INF = (1LL << 60);
//}

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
}

//������
void TestScene::Initialize()
{
	
	/*MakeMazeDigDug(width, height);
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			Map[h][w].X1 = posX1 + w*bSize;
			Map[h][w].X2 = posX2 + w*bSize;
			Map[h][w].Y1 = posY1 + h*bSize;
			Map[h][w].Y2 = posY2 + h*bSize;
			Map[h][w].num = num;
			num++;
			Map[h][w].Weight = rand() % 10;
			if (h == 0 || w == 0 || h == height - 1 || w == width - 1) {
				Map[h][w].State = BOXSTATE::WALL;
				continue;
			}
		}
	}

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			MapDataForSearch[h][w] = Map[h][w].State;
		}
	}

	MapDataForSearch[Start.y][Start.x] = START;
	MapDataForSearch[Goal.y][Goal.x] = GOAL;*/

	
}

//�X�V
void TestScene::Update()
{
	/*BFS();*/
	/*DijkstraMethod();*/
}

//�`��
void TestScene::Draw()
{
	/*DrawMaze(width, height);*/
}

//�J��
void TestScene::Release()
{
}

//void TestScene::AllWall(int w, int h)
//{
//	for (int j = 0; j < h; j++)
//	{
//		for (int i = 0; i < w; i++) {
//			if (i == 0 || j == 0 || i == w - 1 || j == h - 1)
//				Map[j][i].State = ROAD;
//			else
//				Map[j][i].State = WALL;
//		}
//	}
//}
//
//void TestScene::MakeMazeDigDug(int w, int h)
//{
//	AllWall(w, h);
//	Point sp{ 1, 1 };
//	prStack.push(sp);
//	while (!prStack.empty())
//	{
//		sp = prStack.top();
//		prStack.pop();
//		DigDug(sp.x, sp.y);
//	}
//}
//
//void TestScene::DigDug(int x, int y)
//{
//	Map[y][x].State = ROAD;
//	Point Dir[]{ {0,-1},{1, 0},{0, 1},{-1,0} };
//	std::vector<int> dList;
//	for (int i = 0; i < 4; i++) {
//		//next��0~3�܂ŉ񂵂Ăł��[���擾
//		Point next = { x + Dir[i].x,y + Dir[i].y };
//		Point nextNext = { next.x + Dir[i].x,next.y + Dir[i].y };
//
//		if (nextNext.x < 0 || nextNext.y < 0 || nextNext.x > width - 1 || nextNext.y > height - 1)
//			continue;
//
//		if (Map[nextNext.y][nextNext.x].State == WALL)
//		{
//			dList.push_back(i);
//		}
//	}
//	if (dList.empty())
//	{
//		return;
//	}
//	int nrand = rand() % dList.size();
//	int tmp = dList[nrand];
//
//	Point next =  { x + Dir[tmp].x,y + Dir[tmp].y };
//	Point nextNext = { next.x + Dir[tmp].x,next.y + Dir[tmp].y };
//
//	Map[next.y][next.x].State = ROAD;
//	Map[nextNext.y][nextNext.x].State = ROAD;
//
//	prStack.push(nextNext);
//	DigDug(nextNext.x, nextNext.y);
//}
//
//void TestScene::DrawMaze(int _w, int _h)
//{
//	unsigned int col[MAX]{ GetColor(255,255,0), GetColor(255,255,255), GetColor(0,255,255),GetColor(0,255,255) ,GetColor(255,0,0) };//r,w,s,g
//	for (int h = 0; h < _h; h++) {
//		for (int w = 0; w < _w; w++) {
//			switch (MapDataForSearch[h][w]) {
//			case BOXSTATE::ROAD:
//			{
//				DrawBoxAA(Map[h][w].X1, Map[h][w].Y1, Map[h][w].X2, Map[h][w].Y2, col[MapDataForSearch[h][w]], FALSE);
//				break;
//			}
//			case BOXSTATE::WALL:
//			{
//				DrawBoxAA(Map[h][w].X1, Map[h][w].Y1, Map[h][w].X2, Map[h][w].Y2, col[MapDataForSearch[h][w]], TRUE);
//				break;
//			}
//			case BOXSTATE::START:
//			{
//				DrawBoxAA(Map[h][w].X1, Map[h][w].Y1, Map[h][w].X2, Map[h][w].Y2, col[MapDataForSearch[h][w]], TRUE);
//				break;
//			}
//			case BOXSTATE::GOAL:
//			{
//				DrawBoxAA(Map[h][w].X1, Map[h][w].Y1, Map[h][w].X2, Map[h][w].Y2, col[MapDataForSearch[h][w]], TRUE);
//				break;
//			}
//			default: break;
//			}
//
//		}
//	}
//}
//
//void TestScene::MakeWall(int w, int h)
//{
//}
//
//void TestScene::BFS()
//{
//	/*std::queue<std::pair<Point, int>> myQueue;
//
//	Point np[] = { {0,-1},{1, 0},{0, 1},{-1,0} };
//
//	int step = MAX;
//
//	myQueue.push({Start, step});
//
//	MapDataForSearch[Start.x][Start.y] = step;
//
//	while (!myQueue.empty()) {
//		std::pair<Point,int> Crr = myQueue.front();
//		myQueue.pop();
//		for (int i = 0; i < 4; i++) {
//			Point tmp = Crr.first + ;
//			if () {
//				continue;
//			}
//			if (MapDataForSearch[tmp.y][tmp.x] == ROAD) {
//				MapDataForSearch[tmp.y][tmp.x] == ;
//				myQueue.push({ , });
//			}
//		}
//
//	}*/
//
//	// BFS�p�̃L���[
//	std::queue<std::pair<Point, int>> myQueue;  // (���W, �X�e�b�v��)
//
//	// �T�������i�㉺���E�j
//	Point directions[] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };
//
//	// �X�e�b�v����������
//	int step = 1;
//
//	// �X�^�[�g�ʒu���L���[�ɓ����
//	myQueue.push({ Start, step });
//
//	// �T���z��̏������iROAD�͖��T���ASTART�̓X�^�[�g�n�_�j
//	MapDataForSearch[Start.y][Start.x] = step;
//
//	while (!myQueue.empty()) {
//		// �L���[���猻�݂̈ʒu�ƃX�e�b�v�������o��
//		std::pair<Point, int> current = myQueue.front();
//		myQueue.pop();
//
//		// ���݂̍��W�ƃX�e�b�v��
//		Point currentPos = current.first;
//		int currentStep = current.second;
//
//		// �S�[���ɓ��B�����ꍇ
//		if (currentPos.x == Goal.x && currentPos.y == Goal.y) {
//			// �o�H�����������ꍇ�̏�����ǉ��\
//			break;
//		}
//
//		// 4�����ɒT��
//		for (int i = 0; i < 4; i++) {
//			// ���ɐi�ޕ���
//			Point next = { currentPos.x + directions[i].x, currentPos.y + directions[i].y };
//
//			// �͈͊O���ǂ̏ꍇ�̓X�L�b�v
//			if (next.x < 0 || next.y < 0 || next.x >= width || next.y >= height) {
//				continue;
//			}
//
//			// ���łɒT�������ꏊ���ǂȂ�X�L�b�v
//			if (MapDataForSearch[next.y][next.x] != ROAD) {
//				continue;
//			}
//
//			// �X�e�b�v�����L�^
//			MapDataForSearch[next.y][next.x] = currentStep + 1;
//
//			// ���̈ʒu���L���[�ɒǉ�
//			myQueue.push({ next, currentStep + 1 });
//		}
//	}
//
//}
//
//void TestScene::DijkstraMethod(const Graph& graph, std::vector<long long>& distances, int startIndex, int targetIndex, std::vector<int>& path)
//{
//	std::vector<int> p(distances.size(), -1);
//
//	std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> q;
//
//	q.emplace((distances[startIndex] = 0), startIndex);
//
//	while (!q.empty()) {
//		const long long distance = q.top().first;
//		const int from = q.top().second;
//		q.pop();
//
//		if (distances[from] < distance) {
//			continue;
//		}
//
//		for (const auto& edge : graph[from]) {
//			const long long d = (distances[from] + edge.cost);
//
//			if (d < distances[edge.to]) {
//				q.emplace((distances[edge.to] = d), edge.to);
//			}
//		}
//	}
//
//	if (distances[targetIndex] != INF) {
//		for (int i = targetIndex; i != -1; i = p[i]) {
//			path.push_back(i);
//		}
//		std::reverse(path.begin(), path.end());
//	}
//}
//
