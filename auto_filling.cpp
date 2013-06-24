#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#define Setcolor_White {SetConsoleTextAttribute( hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);}
#define Setcolor_Cyan {SetConsoleTextAttribute( hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY);}
#define Setcolor_Green {SetConsoleTextAttribute( hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);}
#define Setcolor_Red {SetConsoleTextAttribute( hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);}
#define Set_Cursor_Position {SetConsoleCursorPosition(hConsole, Position);}
#define Ingame_Message_L1 {Position.X = 40; Position.Y = 14; SetConsoleCursorPosition(hConsole, Position);}
#define Ingame_Message_L2 {Position.X = 40; Position.Y = 16; SetConsoleCursorPosition(hConsole, Position);}
#define Default_Position {Position.X = x; Position.Y = y; SetConsoleCursorPosition(hConsole, Position);}
#define Clear_Message_L1 {Position.X = 40; Position.Y = 14; SetConsoleCursorPosition(hConsole, Position); cout<<"\t\t\t\t\t";}
#define Clear_Message_L2 {Position.X = 40; Position.Y = 16; SetConsoleCursorPosition(hConsole, Position); cout<<"\t\t\t\t\t";}

using namespace std;

void Situate_Random (char **Array, char Hor_or_Vert, char x, char y, char j)
{
	void Mark_Ships(char **Array, char Mark_Value);
	srand(unsigned(time(0)));
	//Первым разместим 4 палубник
	if (Hor_or_Vert==0)//Разместим корабль горизонтально
	{
		x = rand() % 6 + 0; y = rand() % 9 + 0;
		//Присвоим Х и Y такие значения, при которых корабль при размещении выйдет за пределы поля
		for (int i = 0; i < 4; i++)
			Array[y][x+i] = 40;
		//Теперь корабль нужно окружить пометками для того чтобы следующий не разместился слишком близко
		Mark_Ships(Array, 8);
	}
	if (Hor_or_Vert==1)//Разместим корабль вертикально
	{
		x = rand() % 9 + 0;
		y = rand() % 6 + 0;
		//Присвоим Х и Y такие значения, при которых корабль при размещении выйдет за пределы поля
		for (int i=0; i<4; i++)
			Array[y+i][x]=40;
		//Теперь корабль нужно окружить пометками для того чтобы следующий не разместился слишком близко
		Mark_Ships(Array, 8);
	}
	//3-палубники

	for (j = 0; j < 2; j++)
	{
		Hor_or_Vert = rand() % 2;
		if (Hor_or_Vert==0)
		{
			do {
				x=rand()%7+0;
				y=rand()%9+0;
			}
			while (Array[y][x]!=0 || Array[y][x+1]!=0 || Array[y][x+2]!=0); //Находим на поле свободное место

			for (int i = 0; i < 3; i++)
				if (j==0) Array[y][x+i]=30;
				else Array[y][x+i]=31;
			
			Mark_Ships(Array, 8);
		}

		if (Hor_or_Vert==1)
		{
			do {
				x=rand()%9+0;
				y=rand()%7+0;
			}
			while (Array[y][x]!=0 || Array[y+1][x]!=0 || Array[y+2][x]!=0); 
			for (int i = 0; i < 3; i++)
				if (j==0) Array[y+i][x]=30;
				else Array[y+i][x]=31;
			Mark_Ships(Array, 8);
		}
	}

	//2-палубники

	for (j = 0; j < 3; j++)
	{
		Hor_or_Vert = rand() % 2;
		if (Hor_or_Vert==0)
		{
			do {
				x=rand()%8+0;
				y=rand()%9+0;
			}
			while (Array[y][x]!=0 || Array[y][x+1]!=0); 
			for (int i = 0; i < 2; i++)
			{
				if (j==0) Array[y][x+i]=20;
				if (j==1) Array[y][x+i]=21;
				if (j==2) Array[y][x+i]=22;
			}
			Mark_Ships(Array, 8);
		}

		if (Hor_or_Vert==1)
		{
			do {
				x=rand()%9+0;
				y=rand()%8+0;
			}
			while (Array[y][x]!=0 || Array[y+1][x]!=0); 
			for (int i = 0; i < 2; i++)
			{
				if (j==0) Array[y+i][x]=20;
				if (j==1) Array[y+i][x]=21; 
				if (j==2) Array[y+i][x]=22;
			}
			Mark_Ships(Array, 8);
		}
	}
	//1-палубники
	for (j = 0; j < 4; j++)
	{
		do {
			x=rand()%9+0;
			y=rand()%9+0;
		}
		while (Array[y][x]!=0);
		if (j==0) Array[y][x]=10;
		if (j==1) Array[y][x]=11;
		if (j==2) Array[y][x]=12;
		if (j==3) Array[y][x]=13;
		Mark_Ships(Array, 8);
	}
}