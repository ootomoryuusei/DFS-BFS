#include "Player.h"
//#include "./Source/Input.h"
#include "Stage.h"
#include"Enemy.h"
#include "globals.h"
#include "ImGui/imgui.h"

namespace {
    DIR inputDir = NONE;
}

enum {
	MODE_1,
	MODE_2
};

Player::Player(GameObject* parent) 
    : GameObject(parent,"Player") , pos_({CHA_WIDTH, CHA_HEIGHT}), playerImage_(-1)
{
	/*Enemy* pEnemy = GetParent()->FindGameObject<Enemy>();
	isRightHandMove_ = pEnemy->GetIsAIMove().rightHandMove;
	isLeftHandMove_ = pEnemy->GetIsAIMove().leftHandMove;
	isXYCloserRandomMove_ = pEnemy->GetIsAIMove().xyCloserRandomMove;*/
}

Player::~Player()
{
}

void Player::Update()
{
	/*Enemy* pEnemy = GetParent()->FindGameObject<Enemy>();
	pEnemy->SetAIMove(isRightHandMove_, "RightHandMove");
	pEnemy->SetAIMove(isLeftHandMove_, "LeftHandMove");
	pEnemy->SetAIMove(isXYCloserRandomMove_, "XYCloserRandomMove");*/

	int ox = pos_.x, oy = pos_.y;

	if (CheckHitKey(KEY_INPUT_UP))
	{
		pos_.y--;
		inputDir = UP;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		pos_.y++;
		inputDir = DOWN;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		pos_.x--;
		inputDir = LEFT;
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		pos_.x++;
		inputDir = RIGHT;
	}

	/*Stage* stage = (Stage*)FindGameObject<Stage>();*/
	Stage* stage = GetParent()->FindGameObject<Stage>();
	Rect playerRect = { pos_.x, pos_.y, CHA_WIDTH, CHA_HEIGHT };

	for (auto& obj : stage->GetStageRects())
	{
		if (CheckHit(playerRect, obj))
		{
			Rect tmpRectX = { ox, pos_.y, CHA_WIDTH, CHA_HEIGHT };
			Rect tmpRecty = { pos_.x, oy, CHA_WIDTH, CHA_HEIGHT };
			//xŽ²•ûŒü‚Åˆø‚ÁŠ|‚©‚Á‚½
			if (!CheckHit(tmpRectX, obj))
			{
				pos_.x = ox;//xŽ²•ûŒü‚É‚ß‚èž‚ÝC³
				//•ÇƒYƒŠ
				Point centerMe = Rect{ pos_.x, pos_.y, CHA_WIDTH, CHA_HEIGHT }.GetCenter();
				Point centerObj = obj.GetCenter();
				if (centerMe.y > centerObj.y)
				{
					pos_.y++;
				}
				if (centerMe.y < centerObj.y)
				{
					pos_.y--;
				}
			}
			else if (!CheckHit(tmpRecty, obj))
			{
				pos_.y = oy;//y•ûŒü‚Éˆø‚Á‚©‚©‚Á‚½‚ç‚ß‚èž‚ÝC³
				//•ÇƒYƒŠ
				Point centerMe = Rect{ pos_.x, pos_.y, CHA_WIDTH, CHA_HEIGHT }.GetCenter();
				Point centerObj = obj.GetCenter();
				if (centerMe.x > centerObj.x)
				{
					pos_.x++;
				}
				if (centerMe.x < centerObj.x)
				{
					pos_.x--;
				}
			}
			else
			{
				//‚»‚êˆÈŠO‚Åˆø‚ÁŠ|‚©‚Á‚½Žži‚¢‚Â‚â‚ñj
				pos_.x = ox;
				pos_.y = oy;
			}
		}
	}
}

void Player::Draw()
{
	/*ImGui::Begin("SetAIAIMove");
	ImGui::RadioButton("RightHandMove", isRightHandMove_);
	ImGui::RadioButton("LeftHandMove", isLeftHandMove_);
	ImGui::Checkbox("XYCloserRandomMove", &isXYCloserRandomMove_);
	ImGui::End();*/

	DrawBox(pos_.x, pos_.y, pos_.x + CHA_WIDTH, pos_.y + CHA_HEIGHT, GetColor(255, 10, 10), TRUE);
}

bool Player::CheckHit(const Rect& me, const Rect& other)
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
