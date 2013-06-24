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

int Player_Shot( char **Computer_Field, char **Player_Analysis, char CPU_Dk[] )
{
	enum direct {Left = 75 , Right = 77, Up = 72 , Down = 80};

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;

	WORD oldColorAttr;

	GetConsoleScreenBufferInfo(hConsole, &csbi);

	oldColorAttr = csbi.wAttributes;

	COORD Position;

	Setcolor_White;



	char x = 60, y = 10;
	char Key;

	do
	{
		Position.X = x; Position.Y = y;	
		SetConsoleCursorPosition(hConsole, Position);



		Key = _getch();

		switch (Key)
		{
		case Left: if (x > 48) x-=3; break;

		case Right: if (x < 74) x+=3; break;

		case Up: if (y > 2) y-=2; break;

		case Down: if (y < 20) y+=2; break;

		case 'f': case 'F': 

			if (Computer_Field[(y-2)/2][(x-48)/3]==2) break;

			if (!Computer_Field[(y-2)/2][(x-48)/3] || Computer_Field[(y-2)/2][(x-48)/3]==8) 
			{
				Player_Analysis[(y-2)/2][(x-48)/3] = Computer_Field[(y-2)/2][(x-48)/3] = 2;
				cout<<"*"; return 0;
			}


			else

			{
				switch(Computer_Field[(y-2)/2][(x-48)/3])
				{
				case 40: CPU_Dk[0]--; break; case 31: CPU_Dk[1]--; break; case 30: CPU_Dk[2]--; break;
				case 22: CPU_Dk[3]--; break; case 21: CPU_Dk[4]--; break; case 20: CPU_Dk[5]--; break;
				case 13: CPU_Dk[6]--; break; case 12: CPU_Dk[7]--; break; case 11: CPU_Dk[8]--; break;
				case 10: CPU_Dk[9]--; break;
				}
				Player_Analysis[(y-2)/2][(x-48)/3] = Computer_Field[(y-2)/2][(x-48)/3] = 1; return 1;
			}



		}
	}





	while (1);

	SetConsoleTextAttribute(hConsole,oldColorAttr);
}
