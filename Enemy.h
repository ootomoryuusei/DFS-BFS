#pragma once
#include "Engine/GameObject.h"
#include "./globals.h"
#include <vector>

using std::vector;

class Enemy :
    public GameObject
{
public:
    Enemy(GameObject* parent);
    ~Enemy();

    void Update() override;
    void Draw() override;
    bool CheckHit(const Rect& me, const Rect& other);
    void YCloserMove();
    void XCloserMove();
    void XYCloserMove();
    void XYCloserMoveRandom();
    void RightHandMove();
    void LeftHandMove();
    void BFS(Point _start,Point _goal);
    void Dijkstra(Point sp, Point gp);

    void MoveTowardsPlayer();

    AI_MOVEING GetIsAIMove() { return aiMove_; }
private:
    Point pos_;
    bool isAlive_;
    float speed_;
    Point nextPos_;
    DIR forward_;
    vector<vector<int>> dist;
    vector<vector<Point>> pre;

    AI_MOVEING aiMove_;
    const float fixedTime_;
    float time_;

    std::vector<Point> path_; // BFSÇ≈ìæÇΩåoòHÇï€ë∂Ç∑ÇÈ
    int pathIndex_; // åªç›ÇÃêiçsèÛãµ
};