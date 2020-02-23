#include"block.h"
#include<iostream>
#include<conio.h>
#include<windows.h>

using namespace std;

int main()
{
	Map map;
	char a;
	DWORD timer;
	timer = ::GetTickCount64();
	map.show();
	system("pause");
	while (1)
	{
		if (_kbhit())
		{
			a = _getch();
			if (a == 'a')map.move_left();
			if (a == 's')
			{
				if (map.move_down() == 404)break;
			}
			if (a == 'd')map.move_right();
			if (a == 'w')map.transpose();
			if (a == 'p')system("pause");
			if (a == 'x')
			{
				cout << "You exit the game." << endl;
				break;
			}
			map.show();
		}
		if (::GetTickCount64() - timer >= 500)
		{
			timer = ::GetTickCount64();
			if (map.move_down() == 404)break;
			map.show();
		}
	}
	cout << "GAME OVER!" << endl;
	return 0;
}