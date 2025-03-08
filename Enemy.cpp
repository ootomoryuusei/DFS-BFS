#include "Enemy.h"
#include "Stage.h"
#include "globals.h"
#include "Player.h"
#include "ImGui/imgui.h"
#include <map>
#include <queue>

namespace {
    Point nDir[4] = { {0,-1},{0,1},{-1,0},{1,0} };
}

Enemy::Enemy(GameObject* parent)
    : GameObject(parent,"Enemy"),pos_({0,0}), isAlive_(true), nextPos_({0,0}),fixedTime_(10.0f),time_(fixedTime_)
{
	int rx = 0;
	int ry = 0;
	while (rx % 2 == 0 || ry % 2 == 0)
	{
		rx = GetRand(STAGE_WIDTH - 1);
		ry = GetRand(STAGE_HEIGHT - 1);
	}

	pos_ = { rx * CHA_WIDTH, ry * CHA_HEIGHT };
	forward_ = RIGHT;

	dist = vector(STAGE_HEIGHT, vector<int>(STAGE_WIDTH, INT_MAX));
	pre = vector(STAGE_HEIGHT, vector<Point>(STAGE_WIDTH, { -1, -1 }));

	aiMove_ = { true,false,false,false};
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	static bool stop = false;

	if (!stop) {
		Point op = pos_;
		Point move = { nDir[forward_].x, nDir[forward_].y };
		Rect eRect = { pos_.x, pos_.y,CHA_WIDTH, CHA_HEIGHT };
		Stage* stage = GetParent()->FindGameObject<Stage>();
		pos_ = { pos_.x + move.x, pos_.y + move.y };
		for (auto& obj : stage->GetStageRects())
		{
			if (CheckHit(eRect, obj)) {
				Rect tmpRectX = { op.x, pos_.y, CHA_WIDTH, CHA_HEIGHT };
				Rect tmpRecty = { pos_.x, op.y, CHA_WIDTH, CHA_HEIGHT };
				if (!CheckHit(tmpRectX, obj))
				{
					pos_.x = op.x;
				}
				else if (!CheckHit(tmpRecty, obj))
				{
					pos_.y = op.y;
				}
				else
				{
					pos_ = op;
				}
				//forward_ = (DIR)(GetRand(3));
				if (aiMove_.rightHandMove) {
					RightHandMove();
				}
				else if (aiMove_.leftHandMove) {
					LeftHandMove();
				}
				
				break;
			}
		}
	}
	int prgssx = pos_.x % (CHA_WIDTH);
	int prgssy = pos_.y % (CHA_HEIGHT);
	int cx = (pos_.x / (CHA_WIDTH)) % 2;
	int cy = (pos_.y / (CHA_HEIGHT)) % 2;
	if (prgssx == 0 && prgssy == 0 && cx && cy)
	{
		//次、どっちの方向に行くかここに書く！
		if (aiMove_.rightHandMove) {
			RightHandMove();
		}
		if (aiMove_.leftHandMove) {
			LeftHandMove();
		}
		if (aiMove_.xyCloserRandomMove) {
			XYCloserMoveRandom();
		}
		if (aiMove_.pickRorXY) {
			if (time_ <= 0.0f) {
				int rnum = GetRand(1);
				if (rnum == 0) {
					aiMove_.rightHandMove = true;
					aiMove_.xyCloserRandomMove = false;
				}
				else if (rnum == 1) {
					aiMove_.rightHandMove = false;
					aiMove_.xyCloserRandomMove = true;
				}
				time_ = fixedTime_;
			}
			else {
				time_ -= Time::DeltaTime() * 60.0f;
			}
		}
		/*Player* pPlayer = GetParent()->FindGameObject<Player>();
				Dijkstra(this->pos_, pPlayer->GetPos());*/
	}

}

void Enemy::Draw()
{
	DrawBox(pos_.x, pos_.y, pos_.x + CHA_WIDTH, pos_.y + CHA_HEIGHT,
		GetColor(80, 89, 10), TRUE);
	Point tp[4][3] = {
		{{pos_.x + CHA_WIDTH / 2, pos_.y}, {pos_.x, pos_.y + CHA_HEIGHT / 2}, {pos_.x + CHA_WIDTH, pos_.y + CHA_HEIGHT / 2}},
		{{pos_.x + CHA_WIDTH / 2, pos_.y + CHA_HEIGHT}, {pos_.x, pos_.y + CHA_HEIGHT / 2}, {pos_.x + CHA_WIDTH, pos_.y + CHA_HEIGHT / 2}},
		{{pos_.x            , pos_.y + CHA_HEIGHT / 2}, {pos_.x + CHA_WIDTH / 2, pos_.y}, {pos_.x + CHA_WIDTH / 2, pos_.y + CHA_HEIGHT}},
		{{pos_.x + CHA_WIDTH, pos_.y + CHA_HEIGHT / 2}, {pos_.x + CHA_WIDTH / 2, pos_.y}, {pos_.x + CHA_WIDTH / 2, pos_.y + CHA_HEIGHT}}
	};

	DrawTriangle(tp[forward_][0].x, tp[forward_][0].y, tp[forward_][1].x, tp[forward_][1].y, tp[forward_][2].x, tp[forward_][2].y, GetColor(255, 255, 255), TRUE);

	ImGui::Begin("SetAIAIMove");
	// RightHandMoveとLeftHandMoveのラジオボタンを表示
	/*if (ImGui::RadioButton("RightHandMove", aiMove_.rightHandMove)) {
		aiMove_.rightHandMove = true;
		aiMove_.leftHandMove = false;
	}
	if (ImGui::RadioButton("LeftHandMove", aiMove_.leftHandMove)) {
		aiMove_.rightHandMove = false;
		aiMove_.leftHandMove = true;
	}*/
	ImGui::Checkbox("RightHandMove", &aiMove_.rightHandMove);
	ImGui::Checkbox("LeftHandMove", &aiMove_.leftHandMove);
	ImGui::Checkbox("XYCloserRandomMove", &aiMove_.xyCloserRandomMove);
	if (ImGui::Checkbox("RightHandMove or XYCloserRandomMove", &aiMove_.pickRorXY)) {

	}
	ImGui::DragFloat(" : time", &time_);
	ImGui::End();
}

bool Enemy::CheckHit(const Rect& me, const Rect& other)
{
	if (me.x < other.x + other.w &&
		me.x + me.w > other.x &&
		me.y < other.y + other.h &&
		me.y + me.h > other.y)
	{
		return true;
	}
	return false;
}

void Enemy::YCloserMove()
{
	Player* player = GetParent()->FindGameObject<Player>();
	if (pos_.y > player->GetPos().y)
	{
		forward_ = UP;
	}
	else if (pos_.y < player->GetPos().y)
	{
		forward_ = DOWN;
	}
}

void Enemy::XCloserMove()
{
	Player* player = GetParent()->FindGameObject<Player>();
	if (pos_.x > player->GetPos().x)
	{
		forward_ = LEFT;
	}
	else if (pos_.x < player->GetPos().x)
	{
		forward_ = RIGHT;
	}
}

void Enemy::XYCloserMove()
{
	Player* player = GetParent()->FindGameObject<Player>();
	int xdis = abs(pos_.x - player->GetPos().x);
	int ydis = abs(pos_.y - player->GetPos().y);

	if (xdis > ydis) {
		/*if (pos_.x > player->GetPos().x)
		{
			forward_ = LEFT;
		}
		else if (pos_.x < player->GetPos().x)
		{
			forward_ = RIGHT;
		}*/
		XCloserMove();
	}
	else
	{
		/*if (pos_.y > player->GetPos().y)
		{
			forward_ = UP;
		}
		else if (pos_.y < player->GetPos().y)
		{
			forward_ = DOWN;
		}*/
		YCloserMove();
	}
}

void Enemy::XYCloserMoveRandom()
{
	//３分の1の確率でプレイヤーに近い方に行く、残りの3分の1はランダム方向に移動、残りは何もしない
	Player* player = GetParent()->FindGameObject<Player>();
	int xdis = abs(pos_.x - player->GetPos().x);
	int ydis = abs(pos_.y - player->GetPos().y);
	int rnum = GetRand(1);
	if (rnum == 0)
		XYCloserMove();
	else if (rnum == 1)
	{
		forward_ = (DIR)GetRand(3);
	}

}

void Enemy::RightHandMove()
{
	DIR myRight[4] = { RIGHT, LEFT, UP, DOWN };
	DIR myLeft[4] = { LEFT, RIGHT, DOWN, UP };
	Point nposF = { pos_.x + nDir[forward_].x, pos_.y + nDir[forward_].y };
	Point nposR = { pos_.x + nDir[myRight[forward_]].x, pos_.y + nDir[myRight[forward_]].y };
	Rect myRectF{ nposF.x, nposF.y, CHA_WIDTH, CHA_HEIGHT };
	Rect myRectR{ nposR.x, nposR.y, CHA_WIDTH, CHA_HEIGHT };
	Stage* stage = GetParent()->FindGameObject<Stage>();
	bool isRightOpen = true;
	bool isForwardOpen = true;
	for (auto& obj : stage->GetStageRects()) {
		if (CheckHit(myRectF, obj)) {
			isForwardOpen = false;
		}
		if (CheckHit(myRectR, obj)) {
			isRightOpen = false;
		}
	}
	if (isRightOpen)
	{
		forward_ = myRight[forward_];
	}
	else if (isRightOpen == false && isForwardOpen == false)
	{
		forward_ = myLeft[forward_];
	}
}

void Enemy::LeftHandMove()
{
	DIR myRight[4] = { RIGHT, LEFT, UP, DOWN };
	DIR myLeft[4] = { LEFT, RIGHT, DOWN, UP };
	Point nposF = { pos_.x + nDir[forward_].x, pos_.y + nDir[forward_].y };
	Point nposR = { pos_.x + nDir[myLeft[forward_]].x, pos_.y + nDir[myLeft[forward_]].y };
	Rect myRectF{ nposF.x, nposF.y, CHA_WIDTH, CHA_HEIGHT };
	Rect myRectR{ nposR.x, nposR.y, CHA_WIDTH, CHA_HEIGHT };
	Stage* stage = GetParent()->FindGameObject<Stage>();
	bool isLefttOpen = true;
	bool isForwardOpen = true;
	for (auto& obj : stage->GetStageRects()) {
		if (CheckHit(myRectF, obj)) {
			isLefttOpen = false;
		}
		if (CheckHit(myRectR, obj)) {
			isLefttOpen = false;
		}
	}
	if (isLefttOpen)
	{
		forward_ = myLeft[forward_];
	}
	else if (isLefttOpen == false && isForwardOpen == false)
	{
		forward_ = myRight[forward_];
	}
}

void Enemy::Dijkstra(Point sp, Point gp)
{
	using Mdat = std::pair<int, Point>;

	dist[sp.y][sp.x] = 0;
	auto compare = [](const Mdat& a, const Mdat& b) {
		return a.first > b.first; // Compare based on the first value (distance)
		};

	/*std::priority_queue<Mdat, std::vector<Mdat>, std::greater<Mdat>> pq;*/
	std::priority_queue<Mdat, std::vector<Mdat>, decltype(compare)> pq(compare);

	pq.push(Mdat(0, { sp.x, sp.y }));
	vector<vector<StageObj>> stageData = ((Stage*)FindGameObject<Stage>())->GetStageGrid();

	while (!pq.empty())
	{
		Mdat p = pq.top();
		pq.pop();

		//Rect{ (int)p.second.x * STAGE_WIDTH, (int)p.second.y * BLOCK_SIZE.y, BLOCK_SIZE }.draw(Palette::Red);
		//getchar();
		int c = p.first;
		Point v = p.second;

		for (int i = 0; i < 4; i++)
		{
			Point np = { v.x + (int)nDir[i].x, v.y + (int)nDir[i].y };
			if (np.x < 0 || np.y < 0 || np.x >= STAGE_WIDTH || np.y >= STAGE_HEIGHT) continue;
			if (stageData[np.y][np.x].obj == STAGE_OBJ::WALL) continue;
			if (dist[np.y][np.x] <= (int)stageData[np.y][np.x].weight + c) continue;
			dist[np.y][np.x] = stageData[np.y][np.x].weight + c;
			pre[np.y][np.x] = Point({ v.x, v.y });
			pq.push(Mdat(dist[np.y][np.x], np));
		}
	}
}

