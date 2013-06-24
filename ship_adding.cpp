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

void Add_Ship( char **Array, char Floors, char Ship_ID )
{
	enum direct {Left = 75 , Right = 77, Up = 72 , Down = 80, Enter = 13};

	bool Interrupt = 0;

	char Floors_check = 0;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;

	WORD oldColorAttr;

	GetConsoleScreenBufferInfo(hConsole, &csbi);

	oldColorAttr = csbi.wAttributes;

	COORD Position; 

	Setcolor_White;
	Position.X = 45; Position.Y = 1;	
	SetConsoleCursorPosition(hConsole, Position); cout<<"Поставьте "<<int(Floors)<<" - палубник";
	Position.X = 50; Position.Y = 6;	
	SetConsoleCursorPosition(hConsole, Position); cout<<"Управление";
	Position.X = 40; Position.Y = 8;	
	SetConsoleCursorPosition(hConsole, Position); cout<<"S - Установить участок корабля";
	Position.X = 40; Position.Y = 10;	
	SetConsoleCursorPosition(hConsole, Position); cout<<"D - Убрать участок корабля";

	char x = 4, y = 2; 
	char Key; 

	do
	{
		Position.X = x; Position.Y = y;	
		SetConsoleCursorPosition(hConsole, Position);

		if (Floors_check==Floors)
		{
			Ingame_Message_L1; Setcolor_Green; cout<<"Вы поставили корабль.";
			Ingame_Message_L2; cout<<"Enter - далее, D - удалить фрагмент"; Default_Position; 
		}

		Key = _getch();

		switch (Key)
		{
		case Left: if (x > 4) x-=3; break;

		case Right: if (x < 30) x+=3; break;

		case Up: if (y > 2) y-=2; break;

		case Down: if (y < 20) y+=2; break;

		case Enter: if (Floors_check==Floors) 
					{
						Interrupt = 1; break;
					} 
					else
					{
						Clear_Message_L1; Ingame_Message_L1; Setcolor_Red;
						cout<<"Ви еще не поставили корабль."; Default_Position; break;
					}

		case 's': case 'S':

			if (Floors_check==Floors) break;

			if ( y == 2 )
			{
				if ( x == 4 ) 
				{
					if (Array[0][0]==8) 
					{
						Ingame_Message_L1; Set_Cursor_Position; Setcolor_Red; 
						cout<<"Слишком близко к другому"; break;
					}
					if (!Array[0][0]) 
					{
						if (Floors_check)
						{
							if (Array[0][1]==Ship_ID || Array[1][0]==Ship_ID) 
							{
								Array[0][0] = Ship_ID; Floors_check++; Setcolor_Green; 
								cout<<char(135); Clear_Message_L1; Clear_Message_L2; break; 
							} 
							if (Array[0][1]!=Ship_ID && Array[1][0]!=Ship_ID)
							{
								Ingame_Message_L1; Set_Cursor_Position; Setcolor_Red; 
								cout<<"Корабль должен быть монолитным";
							}
						}

						if (Floors_check==0)
						{
							Array[0][0] = Ship_ID; Floors_check++; Setcolor_Green; cout<<char(135); 
							Clear_Message_L1; Clear_Message_L2; break; 
						}
					}

					if (Array[0][0]!=0) 
					{
						Clear_Message_L1; Ingame_Message_L1; Set_Cursor_Position; Setcolor_Red; cout<<"Позиция занята";break;
					}
				}

				if ( x > 4) 
				{
					if (Array[0][(x-4)/3]==8)
					{
						Ingame_Message_L1; Set_Cursor_Position; Setcolor_Red;
						cout<<"Слишком близко к другому"; break;
					}
					if (Array[0][(x-4)/3]==0) 
					{
						if (Floors_check!=0)
						{
							if (Array[0][(x-4)/3-1]==Ship_ID || Array[0][(x-4)/3+1]==Ship_ID || Array[1][(x-4)/3]==Ship_ID) 
							{
								Array[0][(x-4)/3] = Ship_ID; Floors_check++; Setcolor_Green; 
								cout<<char(135);Clear_Message_L1; Clear_Message_L2; break; 
							}
							if (((x-4)/3-1) >= 0 && Array[0][(x-4)/3-1]!=Ship_ID && ((x-4)/3+1) <= 9 && Array[0][(x-4)/3+1]!=Ship_ID && Array[1][(x-4)/3]!=Ship_ID)
							{
								Ingame_Message_L1; Set_Cursor_Position; Setcolor_Red; 
								cout<<"Корабль должен быть монолитным";
							}
						}
						if (Floors_check==0)
						{
							Array[0][(x-4)/3] = Ship_ID; Floors_check++; Setcolor_Green; 
							cout<<char(135);Clear_Message_L1; Clear_Message_L2; break; 
						}

					}

					if (Array[0][(x-4)/3]!=0) 
					{
						Clear_Message_L1; Ingame_Message_L1; Set_Cursor_Position; 
						Setcolor_Red; cout<<"Позиция занята";break;
					}
				}
			}

			if ( y == 20)
			{
				if ( x == 4 ) 
				{
					if (Array[9][0]==8) 
					{
						Ingame_Message_L1; Set_Cursor_Position; Setcolor_Red; 
						cout<<"Слишком близко к другому"; break;
					}
					if (Array[9][0]==0) 
					{
						if (Floors_check!=0)
						{
							if (Array[8][0]==Ship_ID || Array[9][1]==Ship_ID)
							{
								Array[9][0] = Ship_ID; Floors_check++; Setcolor_Green; 
								cout<<char(135);Clear_Message_L1; Clear_Message_L2; break; 
							}
							if (Array[8][0]!=Ship_ID && Array[9][1]!=Ship_ID)
							{
								Ingame_Message_L1; Set_Cursor_Position; Setcolor_Red; 
								cout<<"Корабль должен быть монолитным";
							}
						}

						if (Floors_check==0)
						{
							Array[9][0] = Ship_ID; Floors_check++; Setcolor_Green; 
							cout<<char(135);Clear_Message_L1; Clear_Message_L2; break; 
						}
					}

					if (Array[9][0]!=0) 
					{
						Clear_Message_L1;Ingame_Message_L1; Set_Cursor_Position; Setcolor_Red; 
						cout<<"Позиция занята";break;
					}

				}

				if ( x > 4) 
				{
					if (Array[9][(x-4)/3]==8)
					{
						Ingame_Message_L1; Set_Cursor_Position; Setcolor_Red; 
						cout<<"Слишком близко к другому"; break;
					}
					if (Array[9][(x-4)/3]==0) 
					{
						if (Floors_check!=0)
						{
							if (Array[8][(x-4)/3]==Ship_ID || Array[9][(x-4)/3-1]==Ship_ID || Array[9][(x-4)/3+1]==Ship_ID)
							{
								Array[9][(x-4)/3] = Ship_ID; Floors_check++; Setcolor_Green; 
								cout<<char(135);Clear_Message_L1; Clear_Message_L2; break; 
							}
							if (Array[8][(x-4)/3]!=Ship_ID && Array[9][(x-4)/3-1]!=Ship_ID && Array[9][(x-4)/3+1]!=Ship_ID)
							{
								Ingame_Message_L1; Set_Cursor_Position; Setcolor_Red; 
								cout<<"Корабль должен быть монолитным";
							}
						}

						if (Floors_check==0)
						{
							Array[9][(x-4)/3] = Ship_ID; Floors_check++; Setcolor_Green; 
							cout<<char(135);Clear_Message_L1; Clear_Message_L2; break; 
						}
					}

					if (Array[9][(x-4)/3]!=0) 
					{
						Clear_Message_L1;Ingame_Message_L1; Set_Cursor_Position; Setcolor_Red; 
						cout<<"Позиция занята";break;
					}
				}
			}

			if (y > 2 && y < 20)
			{
				if ( x == 4 ) 
				{
					if (Array[(y-2)/2][0]==8)
					{
						Ingame_Message_L1; Set_Cursor_Position; Setcolor_Red; 
						cout<<"Слишком близко к другому"; break;
					}
					if (Array[(y-2)/2][0]==0) 
					{
						if (Floors_check!=0)
						{
							if (Array[(y-2)/2-1][0]==Ship_ID|| Array[(y-2)/2+1][0]==Ship_ID||Array[(y-2)/2][1]==Ship_ID)
							{
								Array[(y-2)/2][0] = Ship_ID; Floors_check++; Setcolor_Green; 
								cout<<char(135);Clear_Message_L1; Clear_Message_L2; break; 
							}
							if (Array[(y-2)/2-1][0]!=Ship_ID && Array[(y-2)/2+1][0]!=Ship_ID && Array[(y-2)/2][1]!=Ship_ID)
							{
								Ingame_Message_L1; Set_Cursor_Position; Setcolor_Red; 
								cout<<"Корабль должен быть монолитным";
							}
						}

						if (Floors_check==0)
						{
							Array[(y-2)/2][0] = Ship_ID; Floors_check++; Setcolor_Green; 
							cout<<char(135);Clear_Message_L1; Clear_Message_L2; break; 
						}
					}

					if (Array[(y-2)/2][0]!=0) 
					{
						Clear_Message_L1; Ingame_Message_L1; Set_Cursor_Position; Setcolor_Red; 
						cout<<"Позиция занята"; break;
					}

				}

				if ( x > 4 ) 
				{
					if (Array[(y-2)/2][(x-4)/3]==8)
					{
						Ingame_Message_L1; Set_Cursor_Position; Setcolor_Red; 
						cout<<"Слишком близко к другому"; break;
					}
					if (Array[(y-2)/2][(x-4)/3]==0) 
					{
						if (Floors_check!=0)
						{
							if (Array[(y-2)/2-1][(x-4)/3]==Ship_ID || Array[(y-2)/2+1][(x-4)/3]==Ship_ID || Array[(y-2)/2][(x-4)/3-1]==Ship_ID || x < 30 && Array[(y-2)/2][(x-4)/3+1]==Ship_ID)
							{
								Array[(y-2)/2][(x-4)/3] = Ship_ID; Floors_check++; Setcolor_Green; 
								cout<<char(135);Clear_Message_L1; Clear_Message_L2; break; 
							}
							if (Array[(y-2)/2-1][(x-4)/3]!=Ship_ID && Array[(y-2)/2+1][(x-4)/3]!=Ship_ID && Array[(y-2)/2][(x-4)/3-1]!=Ship_ID && Array[(y-2)/2][(x-4)/3+1]!=Ship_ID)
							{
								Ingame_Message_L1; Set_Cursor_Position; Setcolor_Red; 
								cout<<"Корабль должен быть монолитным";
							}
						}

						if (Floors_check==0)
						{
							Array[(y-2)/2][(x-4)/3] = Ship_ID; Floors_check++; Setcolor_Green; 
							cout<<char(135);Clear_Message_L1; Clear_Message_L2; break; 
						}
					}
					if (Array[(y-2)/2][(x-4)/3]!=0) 
					{
						Clear_Message_L1; Ingame_Message_L1; Set_Cursor_Position; Setcolor_Red; 
						cout<<"Позиция занята"; break;
					}
				}
			}	

		case 'd': case 'D': 

			if ( y == 2 )
			{
				if ( x == 4 ) 
				{
					if (Array[0][0]==0 || Array[0][0]==8 || Array[0][0]!=Ship_ID) 
						break;

					if (Array[0][0]!=0) 
					{
						Array[0][0]=0; Floors_check--; Setcolor_Cyan; 
						cout<<char(183);Clear_Message_L1; Clear_Message_L2; break;
					}
				}

				if ( x > 4) 
				{
					if (Array[0][(x-4)/3]==0 || Array[0][(x-4)/3]==8 || Array[0][(x-4)/3]!=Ship_ID) 
						break;
					if (Array[0][(x-4)/3]!=0) 
					{
						Array[0][(x-4)/3]=0; Floors_check--; Setcolor_Cyan; 
						cout<<char(183);Clear_Message_L1; Clear_Message_L2; break;
					}
				}
			}

			if ( y == 20)
			{
				if ( x == 4 ) 
				{
					if (Array[9][0]==0 || Array[9][0]==8 || Array[9][0]!=Ship_ID) 
						break;
					if (Array[9][0]!=0) 
					{
						Array[9][0]=0; Floors_check--; Setcolor_Cyan; 
						cout<<char(183);Clear_Message_L1; Clear_Message_L2; break;
					}
				}

				if ( x > 4) 
				{
					if (Array[9][(x-4)/3]==0 || Array[9][(x-4)/3]==8 || Array[9][(x-4)/3]!=Ship_ID) 
						break;
					if (Array[9][(x-4)/3]!=0) 
					{
						Array[9][(x-4)/3]=0; Floors_check--; Setcolor_Cyan; 
						cout<<char(183);Clear_Message_L1; Clear_Message_L2; break;
					}
				}
			}

			else
			{
				if ( x == 4 ) 
				{
					if (Array[(y-2)/2][0]==0 || Array[(y-2)/2][0]==8 || Array[(y-2)/2][0]!=Ship_ID) 
						break;
					if (Array[(y-2)/2][0]!=0) 
					{
						Array[(y-2)/2][0]=0; Floors_check--; Setcolor_Cyan; 
						cout<<char(183);Clear_Message_L1; Clear_Message_L2; break;
					}
				}

				if ( x > 4) 
				{
					if (Array[(y-2)/2][(x-4)/3]==0 || Array[(y-2)/2][(x-4)/3]==8 || Array[(y-2)/2][(x-4)/3]!=Ship_ID) 
						break;
					if (Array[(y-2)/2][(x-4)/3]!=0) 
					{
						Array[(y-2)/2][(x-4)/3]=0; Floors_check--; Setcolor_Cyan; 
						cout<<char(183);Clear_Message_L1; Clear_Message_L2; break;
					}
				}
			}
		}
	}

	while (Interrupt!=1);

	SetConsoleTextAttribute(hConsole,oldColorAttr); 
}