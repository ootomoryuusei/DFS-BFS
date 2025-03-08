#pragma once
#include "Engine/GameObject.h"
#include "globals.h"

class Player :
    public GameObject
{
public:
    Player(GameObject* parent);
    ~Player();
    Point GetPos() { return pos_; }
    void Update() override;
    void Draw() override;
    bool CheckHit(const Rect& me, const Rect& other);
private:
    int playerImage_;
    Point pos_;

    bool isRightHandMove_;
    bool isLeftHandMove_;
    bool isXYCloserRandomMove_;
  /*  bool radioButton_;*/
};