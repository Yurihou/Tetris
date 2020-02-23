#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include"block.h"

using namespace std;

/*
数组下标1代表：0：O；1：I；2：横I；3-6：T的四个方向；7-10：L的四个方向；
11-14：J的四个方向；15、16：Z的两个方向；17、18：S的两个方向。
下标2代表第n个方块。
*/

const int first[19][4] =
{
	{4,5,4,5},{5,5,5,5},{4,5,6,7},{4,5,6,5},{4,4,4,5},{4,5,6,5},{5,5,5,4},{4,4,4,5},{4,5,6,6},{4,5,5,5},{4,5,6,4},
{4,5,5,5},{4,5,6,6},{4,4,4,5},{4,4,5,6},{4,5,5,6},{4,4,5,5},{4,5,5,6},{4,4,5,5}
};
const int second[19][4] =
{
	{0,0,1,1},{0,1,2,3},{0,0,0,0},{0,0,0,1},{0,1,2,1},{1,1,1,0},{0,1,2,1},{0,1,2,2},{1,1,1,0},{0,0,1,2},{0,0,0,1},
{2,0,1,2},{0,0,0,1},{0,1,2,0},{0,1,1,1},{0,0,1,1},{1,2,0,1},{1,1,0,0},{0,1,1,2}
};

Block::Block()
{
	body[0].first = 4;
	body[0].second = 0;
	body[1].first = 5;
	body[1].second = 0;
	body[2].first = 4;
	body[2].second = 1;
	body[3].first = 5;
	body[3].second = 1;
	srand((int)time(0));
	style = rand() % 19;
	next = rand() % 19;
	movement = 0;
	shift = 0;
}

Block::Block(int s)
{
	for (int i = 0; i < 4; i++)
	{
		body[i].first = first[s][i];
		body[i].second = second[s][i];
	}
	style = s;
	movement = 0;
	shift = 0;
}

Block::Block(const Block& b)
{
	for (int i = 0; i < 4; i++)
	{
		body[i].first = b.body[i].first;
		body[i].second = b.body[i].second;
	}
	style = b.style;
	movement = b.movement;
	shift = b.shift;
	next = b.next;
}

void Block::transpose()
{
	if (style == 1)style = 2;
	else if (style == 2)style = 1;//I
	else if (style == 3)style = 4;
	else if (style == 4)style = 5;
	else if (style == 5)style = 6;
	else if (style == 6)style = 3;//T
	else if (style == 7)style = 8;
	else if (style == 8)style = 9;
	else if (style == 9)style = 10;
	else if (style == 10)style = 7;//L
	else if (style == 11)style = 12;
	else if (style == 12)style = 13;
	else if (style == 13)style = 14;
	else if (style == 14)style = 11;//J
	else if (style == 15)style = 16;
	else if (style == 16)style = 15;//S
	else if (style == 17)style = 18;
	else if (style == 18)style = 17;//Z

	for (int i = 0; i < 4; i++)
	{
		body[i].first = first[style][i];
		body[i].second = second[style][i];
	}
}

void Block::renew()
{
	style = next;
	srand((int)time(0));
	next = rand() % 19;
	for (int i = 0; i < 4; i++)
	{
		body[i].first = first[style][i];
		body[i].second = second[style][i];
	}
	movement = 0;
	shift = 0;

}

void Block::move_down()
{
	movement++;
}

void Block::move_left()
{
	shift--;
}

void Block::move_right() 
{
	shift++;
}

Map::Map()
{
	
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			grid[i][j] = 0;
		}
	}
	score = 0;
	block.renew();
}

int Map::is_cascaded(Block temp)
{
	for (int i = 0; i < 4; i++)
	{
		if (temp.body[i].second + temp.movement > 19 || temp.body[i].first + temp.shift > 9 || temp.body[i].first + temp.shift < 0)return 1;
		if (grid[temp.body[i].second + temp.movement][temp.body[i].first + temp.shift] != 0)return 1;
	}
	return 0;
}

int Map::is_bottom()
{
	for (int i = 0; i < 4; i++)
	{
		if (block.body[i].second + block.movement >= 20)return 1;
		if (grid[block.body[i].second + block.movement + 1][block.body[i].first + block.shift] != 0)return 1;
		
	}
	return 0;
}

int Map::find_full_colomn()
{
	int mark = 0;
	int score = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			mark = 1;
			if (grid[i][j] == 0)
			{
				mark = 0;
				break;
			}
		}
		if (mark == 1)
		{
			score++;
			for (int k = i; k > 0; k--)
			{
				for (int j = 0; j < 10; j++)
				{
					grid[k][j] = grid[k - 1][j];
				}
			}
			for (int j = 0; j < 10; j++)
			{
				grid[0][j] = 0;
			}
		}
	}
	return score;
}

int Map::transpose()
{
	Block temp(block);
	temp.transpose();
	if (!is_cascaded(temp))
	{
		block = temp;
		return 0;
	}
	return 1;
}

int Map::move_down()
{
	Block temp(block);
	if (is_bottom())
	{
		for (int i = 0; i < 4; i++)
		{
			grid[block.body[i].second + block.movement][block.body[i].first + block.shift] = 1;
		}
		score += find_full_colomn();
		block.renew();
		if (is_cascaded(block))return 404;
		return -1;
	}
	temp.move_down();
	if (!is_cascaded(temp))
	{
		block = temp;
		return 0;
	}
	return 1;
}

int Map::move_left()
{
	Block temp(block);
	temp.move_left();
	if (!is_cascaded(temp))
	{
		block = temp;
		return 0;
	}
	return 1;
}

int Map::move_right()
{
	Block temp(block);
	temp.move_right();
	if (!is_cascaded(temp))
	{
		block = temp;
		return 0;
	}
	return 1;
}

void Map::show()
{
	int display_buffer[20][10] = { 0 };
	int next_buffer[4][4] = { 0 };

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			display_buffer[i][j] = grid[i][j];
		}
	}
	for (int i = 0; i < 4; i++)
	{
		display_buffer[block.body[i].second + block.movement][block.body[i].first + block.shift] = -1;
	}
	for (int i = 0; i < 4; i++)
	{
		next_buffer[second[block.next][i]][first[block.next][i] - 4] = 1;
	}
	system("cls");
	cout<<"┌────────────────────┬───────────┐"<<endl;
	for (int i = 0; i < 20; i++)
	{
		cout << "│";
		for (int j = 0; j < 10; j++)
		{
			if (display_buffer[i][j] == 0)cout << "  ";
			else if (display_buffer[i][j] == 1)cout << "■";
			else if (display_buffer[i][j] == -1)cout << "□";
		}
		if (i == 0)cout << "│   TETRIS  │" << endl;
		else if (i == 1 || i == 3 || i == 8 || i == 10)cout << "├───────────┤" << endl;
		else if (i == 2)cout << "│    NEXT   │" << endl;
		else if (i >= 4 && i <= 7)
		{
			cout << "│  ";
			for (int l = 0; l < 4; l++)
			{
				if (next_buffer[i - 4][l] == 0)cout << "  ";
				else if (next_buffer[i - 4][l] == 1)cout << "□";
			}
			cout << " │" << endl;
		}
		else if (i == 9)cout << "│ SCORE:" << setw(4) << score << "│" << endl;
		else cout << "│           │" << endl;
	}
	cout << "└────────────────────┴───────────┘" << endl;
}