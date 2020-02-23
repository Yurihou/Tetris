#pragma once

#include<utility>

using namespace std;

typedef pair<int, int> point;

class Block
{
public:
	point body[4];
	int movement;
	int shift;
	int style;
	int next;

	Block();
	Block(int s);
	Block(const Block& b);

	void renew();

	void transpose();
	void move_down();
	void move_left();
	void move_right();
};

class Map
{
public:
	int grid[20][10];
	Block block;
	
	int score;

	Map();

	int is_cascaded(Block temp);
	int is_bottom();
	int find_full_colomn();

	int transpose();
	int move_down();
	int move_left();
	int move_right();

	void show();
};