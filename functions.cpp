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
#define Setcolor_Blue {SetConsoleTextAttribute( hConsole, FOREGROUND_BLUE  | FOREGROUND_INTENSITY);}

using namespace std;


void Splash_Screen ( char **Array, char **Passive_Array )
{
	void Transition(); 
	void Filling_Choice(char **Array, char **Passive_Array);

	enum direct {Up = 72 , Down = 80, Enter = 13};

	int x = 53;
	int y = 6;
	char Key;
	bool Exit = 0;

	HANDLE hConsole  = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	COORD Position;
	setlocale(0, "Russian");
	system("color 0f");
	system("cls");
	cout<<"            8\n             88\n             8_88\n             888\n             88_§§§.\n";
	cout<<"           888_§§§§§\n           8_8_§§§§§§\n          88_8__§§§§§§\n         888_8__§§§§§§§\n";
	cout<<"        8888_8__§§§§§§§§\n       88888_8__§§§§§§§§\n     8888888_8__§§§§§§§§§\n    88888888_8_§§§§§§§§§§§\n";
	cout<<" 8_888888888_8_§§§§§§§§§§§\n 88_8________888_____88888___88\n";
	cout<<"  88888888888888888888888_8888.\n   88888888888888888888888888\n";
	Setcolor_Cyan;
	cout<<"_..-+*°*+-.._ ~~~*°*~~~ _..-+*°*+-.._..-+*°*+-.._ ~~~*°*~~~ _..-+*°*+-.._\n";
	cout<<"~~~ _..-+*°*+-..~~~~ _..-+*°*+-.._~~~ _..-+*°*+-..~~~~ _..-+*°*+-.._\n";
	cout<<"_..-+*~~°*+-..__..-+*~~~~°*+-.._*+-…-+*°_..-+*~~°*+-..__..-+*~~~~°*+-.._*+-…-+*\n\n";
	Setcolor_White;
	cout<<"================================================================================\n";
	cout<<"================================================================================";
	cout<<"========================  (c) Èëüÿ Òåðåùóê (2011)  =============================\n";
	Position.X = 50; Position.Y = 0; SetConsoleCursorPosition(hConsole, Position);
	cout<<"****************************";
	Position.X = 50; Position.Y = 1; SetConsoleCursorPosition(hConsole, Position);
	cout<<"*       ÌÎÐÑÊÎÉ ÁÎÉ       *";
	Position.X = 50; Position.Y = 2; SetConsoleCursorPosition(hConsole, Position);
	cout<<"****************************";
	Position.X = 50; Position.Y = 4; SetConsoleCursorPosition(hConsole, Position);
	cout<<"----------------------------";
	Position.X = 56; Position.Y = 6; SetConsoleCursorPosition(hConsole, Position);
	cout<<"ÍÀ×ÀÒÜ";
	Position.X = 56; Position.Y = 9; SetConsoleCursorPosition(hConsole, Position);
	cout<<"ÂÛÕÎÄ ";
	Position.X = 50; Position.Y = 11; SetConsoleCursorPosition(hConsole, Position);
	cout<<"----------------------------"; 

	do
	{
		if (y==9) 
		{
			Setcolor_Red;
			Position.X = 15;
			Position.Y = 22; 
			SetConsoleCursorPosition(hConsole, Position); 
			cout<<"Enter - Âûõîä           ";
		}
		if (y==6) 
		{
			Setcolor_Green;
			Position.X = 15;
			Position.Y = 22; 
			SetConsoleCursorPosition(hConsole, Position); 
			cout<<"Enter - Íà÷àòü (F-îãîíü)";
		}
		Position.X = x;
		Position.Y = y;	
		SetConsoleCursorPosition(hConsole, Position);

		cout<<">>";
		Key = _getch();

		switch (Key)
		{
		case Up: 
			if (y > 6) 
			{ 
				Position.X = x;
				Position.Y = y; 
				SetConsoleCursorPosition(hConsole, Position); 
				cout<<"  ";
				y-=3;
			} break;

		case Down: 
			if (y < 9)
			{
				Position.X = x;
				Position.Y = y;	
				SetConsoleCursorPosition(hConsole, Position); 
				cout<<"  ";
				y+=3;
			} break;

		case Enter: 
			if (y==9) exit(0); 
			else 
			{
				Transition();
				Filling_Choice(Array, Passive_Array); 
				Exit = 1;
				break;
			}
		}
	} while (Exit!=1);
}

void Clear ( char **Array, char Width, char Height )
{
	for ( char i = 0; i < Height; i++ )
		for ( char j = 0; j < Width; j++ ) 
			Array[i][j] = 0;
}


void Show_Field ( char **Player, char **Analysis, char Width, char Height, bool Amount ) 
{
	HANDLE hConsole  = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	WORD oldColorAttr;
	oldColorAttr = csbi.wAttributes;

	Setcolor_White;

	cout<<"    ";

	for (char Letter = 'A'; Letter <= 'J'; Letter++) cout<<Letter<<"  ";

	if (Amount==1)
	{
		cout<<"\t\t";
		for (char Letter = 'A'; Letter <= 'J'; Letter++) cout<<Letter<<"  ";
	}

	for ( char Number = 1; Number <= 10; Number++ )
	{
		if (Number==10) cout<<"\n\n"<<int(Number);
		else cout<<"\n\n"<<int(Number)<<' '; 

		for ( int Row = 0; Row < 10; Row++ ) 
		{
			if(Player[Number-1][Row] >= 10 && Player[Number-1][Row] <= 40) 
			{
				cout<<"  "; 
				Setcolor_Green;
				cout<<'#';
				SetConsoleTextAttribute(hConsole,oldColorAttr);
			}

			if(Player[Number-1][Row]==8) 
			{
				cout<<"  "; 
				Setcolor_Cyan;
				cout<<char(183);
				SetConsoleTextAttribute(hConsole,oldColorAttr);
			}

			if(Player[Number-1][Row]==1) 
			{
				cout<<"  "; 
				Setcolor_Red;
				cout<<"X";
				SetConsoleTextAttribute(hConsole,oldColorAttr);
			}
			if(Player[Number-1][Row]==2) 
			{
				cout<<"  "; 
				Setcolor_Blue;
				cout<<"*";
				SetConsoleTextAttribute(hConsole,oldColorAttr);
			}

			if(Player[Number-1][Row]==5) 
			{
				cout<<"  "; 
				Setcolor_Red;
				cout<<"5";
				SetConsoleTextAttribute(hConsole,oldColorAttr);
			}

			if(!Player[Number-1][Row])
			{
				Setcolor_White;
				cout<<"  "; 
				cout<<char(183);
				SetConsoleTextAttribute(hConsole,oldColorAttr);
			} 
		}

		if (Amount==1)
		{
			if (Number==10) cout<<"\t    "<<int(Number);
			else cout<<"\t    "<<int(Number)<<' ';

			for (int Row = 0; Row < 10; Row++) 
			{
				if(Analysis[Number-1][Row] >= 10 && Analysis[Number-1][Row] <= 40) 
				{
					cout<<"  "; 
					Setcolor_Green;
					cout<<'#';
					SetConsoleTextAttribute(hConsole,oldColorAttr); 
				}
				if(Analysis[Number-1][Row]==1) 
				{
					cout<<"  "; 
					Setcolor_Red;
					cout<<"X";
					SetConsoleTextAttribute(hConsole,oldColorAttr);
				}
				if(Analysis[Number-1][Row]==2) 
				{
					cout<<"  "; 
					Setcolor_Blue;
					cout<<"*";
					SetConsoleTextAttribute(hConsole,oldColorAttr);
				}
				if(Analysis[Number-1][Row]==5) 
				{
					cout<<"  "; 
					Setcolor_Red;
					cout<<"5";
					SetConsoleTextAttribute(hConsole,oldColorAttr);
				}
				if(!Analysis[Number-1][Row])
				{
					Setcolor_White;
					cout<<"  "; 
					cout<<char(183);
					SetConsoleTextAttribute(hConsole,oldColorAttr);
				} 
				if(Analysis[Number-1][Row]==8) 
				{
					cout<<"  "; 
					Setcolor_Cyan;
					cout<<char(183);
					SetConsoleTextAttribute(hConsole,oldColorAttr);
				}
			}
		}
	}
}

void Mark_Ships( char **Array, char Mark_Value )
{
	for (char i = 0; i < 10; i++)
	{
		for (char j = 0; j < 10; j++)
		{
			if (Array[i][j]==40 || Array[i][j]==30 || Array[i][j]==31 || Array[i][j]==20 || Array[i][j]==21 || Array[i][j]==22 || Array[i][j]==10 || Array[i][j]==11 || Array[i][j]==12 || Array[i][j]==13 || Array[i][j]==9 || Array[i][j]==1) 
			{
				if (i < 9 && Array[i+1][j]==0) Array[i+1][j]=Mark_Value; 
				if (i > 0 && Array[i-1][j]==0) Array[i-1][j]=Mark_Value; 
				if (j < 9 && Array[i][j+1]==0) Array[i][j+1]=Mark_Value; 
				if (j > 0 && Array[i][j-1]==0) Array[i][j-1]=Mark_Value; 
				if (i > 0 && j > 0 && Array[i-1][j-1]==0) Array[i-1][j-1]=Mark_Value;
				if (i > 0 && j < 9 && Array[i-1][j+1]==0) Array[i-1][j+1]=Mark_Value; 
				if (i < 9 && j < 9 && Array[i+1][j+1]==0) Array[i+1][j+1]=Mark_Value; 
				if (i < 9 && j > 0 && Array[i+1][j-1]==0) Array[i+1][j-1]=Mark_Value; 
			}
			Array[i][j]==5 ? Array[i][j] = 2 : 0; 
		}
	}
}

void Situate_Manual (char **Array, char **Passive_Array )
{
	void Add_Ship(char **Array, char Floors, char Ship_ID);
	system("color 0f");
	int q = 0;
	for (int i = 4; i >= 1; i--)
	{
		for (int j = 0; j <= q; j++)
		{
			Show_Field (Array, Passive_Array, 10, 10, 0); 
			Add_Ship(Array, i, i*10+j); 
			system("cls"); 
			Mark_Ships(Array, 8);
		}
		q += 1;
	}
}

void Transition() 
{
	int x = 0; int y = 0, j, symb = 79;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	COORD Position;
	y = 0;
	for (int i = 0; i < 27; i++)
	{
		for (int i = y; i <= y + 8; i++)
		{
			Position.X = x; Position.Y = i; Set_Cursor_Position;
			for (j = symb; j >= 0; j--) cout<<' ';
			x+=5;
			symb-=10; 
		}
		x = 0;
		symb = 79;
		y++;
		Sleep(20); 
	}
	Position.X = 0;
	Position.Y = 0;
	Set_Cursor_Position;
}

void Filling_Choice ( char **Array, char **Passive_Array )
{
	void Situate_Random (char **Array, char Hor_or_Vert, char x, char y, char j);
	enum direct {Up = 72 , Down = 80, Enter = 13};
	char x = 25,
		y = 8,
		Key;
	bool Exit = 0;
	HANDLE hConsole  = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	COORD Position;

	system("color 0f");

	for (char i = 1; i <= 2; i++)
	{
		for (char j = 1; j <= 79; j++) cout<<"#";
		cout<<"\n";
	}

	for (char i = 1; i <=16; i++)
	{
		cout<<"###"; 
		for (char i = 1; i <= 73; i++) cout<<' '; 
		cout<<"###\n";
	}

	for (char i = 1; i <= 2; i++)
	{
		for (char j = 1; j <= 79; j++) cout<<"#";
		cout<<"\n";
	}

	cout<<"\n";

	for (char i = 1; i <= 79; i++) cout<<"=";

	cout<<"\n\n";

	for (char i = 1; i <= 79; i++) cout<<"=";

	Position.X = 28;
	Position.Y = 8;
	Set_Cursor_Position;
	cout<<"ÀÂÒÎÌÀÒÈ×ÅÑÊÎÅ ÇÀÏÎËÍÅÍÈÅ ÏÎËß";
	Position.X = 28;
	Position.Y = 11;
	Set_Cursor_Position;
	cout<<"ÇÀÏÎËÍÈÒÜ ÏÎËÅ ÂÐÓ×ÍÓÞ";

	do
	{
		if (y==11) 
		{
			Setcolor_Green;
			Position.X = 15;
			Position.Y = 22; 
			Set_Cursor_Position; 
			cout<<"Ðàçìåñòèòå êîðàáëè íà ñâîå óñìîòðåíèå        ";
		}

		if (y==8) 
		{
			Setcolor_Green;
			Position.X = 15;
			Position.Y = 22; 
			Set_Cursor_Position; 
			cout<<"Êîìïüþòåð ðàññòàâèò ñóäíà â ñëó÷àéíîì ïîðÿäêå";
		}
		Position.X = x;
		Position.Y = y;	
		Set_Cursor_Position;
		cout<<">>";
		Key = _getch();

		switch (Key)
		{
		case Up: 
			if (y > 8) 
			{ 
				Position.X = x;
				Position.Y = y; 
				Set_Cursor_Position; 
				cout<<"  ";
				y-=3; 
			} break;

		case Down: 
			if (y < 11)
			{
				Position.X = x;
				Position.Y = y;	
				SetConsoleCursorPosition(hConsole, Position); 
				cout<<"  ";
				y+=3; 
			} break;

		case Enter: 
			if (y==8) 
			{
				system("cls");
				Situate_Random (Array, 0, 8, 8, 0);
				system("cls"); 
				Exit = 1;
				break; 
			} 
			else 
			{
				system("cls");
				Situate_Manual(Array, Passive_Array);
				system("cls"); 
				Exit = 1;
				break;
			}
		}
	} while (Exit!=1);
}

void Show_Score ( char CPU_Score, char Player_Score )
{
	HANDLE hConsole  = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	COORD Position;

	Position.X = 0; Position.Y = 22; 
	SetConsoleCursorPosition(hConsole, Position);
	Setcolor_White;
	for (char i = 0; i < 79; i++) cout<<"=";
	cout<<endl<<"\t   ÏÎËÅ ÈÃÐÎÊÀ\t\t\t\t       ÏÎËÅ ÊÎÌÏÜÞÒÅÐÀ\n";
	for (char i = 0; i < 79; i++) cout<<"=";
	cout<<endl<<"\t   ÈÃÐÎÊ: "<<int(Player_Score)<<"\t\t\t\t       ÊÎÌÏÜÞÒÅÐ: "<<int(CPU_Score)<<endl;
	for (char i = 0; i < 79; i++) cout<<"=";
}

char Score( char **Array)
{
	char Score = 0;
	for (char i = 0; i < 10; i++)
	{
		for (char j = 0; j < 10; j++)
			if(Array[i][j]==1) Score++;
	}
	return Score;
}

