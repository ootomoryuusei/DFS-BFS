#pragma once
struct Point
{
	int x, y;
};

struct Pointf
{
	float x, y;
};

struct Rect
{
	int x, y, w, h;
	Rect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}
	Point GetCenter() { return Point{ x + w / 2, y + h / 2 }; }
};


enum STAGE_OBJ {
	EMPTY,
	WALL,
	GOAL,
	MAX_OBJECT
};

struct StageObj
{
	STAGE_OBJ obj;
	float weight;
};


enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE,
	MAXDIR
};

struct AI_MOVEING
{
	bool rightHandMove;
	bool leftHandMove;
	bool xyCloserMove;
	bool xyCloserRandomMove;
	bool pickRorXY;
	bool BFS;
	bool Dijkstra;
};

const int CHA_WIDTH = 32;
const int CHA_HEIGHT = 32;