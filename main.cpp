#include <iostream>
#include <conio.h>
#include <windows.h>
#include "functions_header.h"
#define Setcolor_Cyan {SetConsoleTextAttribute( hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY);}
#define Setcolor_Green {SetConsoleTextAttribute( hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);}
#define Setcolor_Red {SetConsoleTextAttribute( hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);}
#define Setcolor_White {SetConsoleTextAttribute( hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);}
using namespace std;

void main()
{
	HANDLE hConsole  = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	COORD Position;
	setlocale(0, "Russian");

	//Численности палуб всех уникальных кораблей
	char CPU_Dk[10], Player_Dk[10];
	
	char *Dcnt = new char; 
	*Dcnt = 4;

	for (char i = 0; i < 10; i++)
	{
		CPU_Dk[i] = Player_Dk[i] = *Dcnt;
		i == 0 ? (*Dcnt)-- : 0;
		i == 2 ? (*Dcnt)-- : 0;
		i == 5 ? (*Dcnt)-- : 0;
	}
	delete Dcnt;

	for (char i = 0; i < 10; i++) cout<<int(Player_Dk[i])<<"  "; 
	
	char **Analysis = new char *[10];
	for ( register char i = 0; i < 10; i++ ) Analysis[i] = new char [10];
	
	char **Computer_Field = new char *[10];
	for ( register char i = 0; i < 10; i++ ) Computer_Field[i] = new char [10];
	
	char **Player_Field = new char *[10];
	for ( register char i = 0; i < 10; i++ ) Player_Field[i] = new char [10];
	
	char **Computer_Analysis = new char *[10];
	for ( register char i = 0; i < 10; i++ ) Computer_Analysis[i] = new char [10];
	
	Clear(Player_Field, 10, 10);
	Clear(Analysis, 10, 10);
	Clear(Computer_Field, 10, 10);
	Clear(Computer_Analysis, 10, 10);

	Splash_Screen(Player_Field, Analysis); //Вход
	Situate_Random (Computer_Field, 1, 5, 5, 0);

	bool Random_Shot (char **Analysis, char **Player, char Player_Dk[]);
	char Blind_Marked_Shot (char **Analysis, char **Player, char Player_Dk[], char i, char j);
	bool Predicted_Marked_Shot (char **Analysis, char **Player, char Hor_or_Vert, char Player_Dk[]);
	char Score( char **Array);
	void Show_Score ( char CPU_Score, char Player_Score );

	int Player_Shot( char **Computer_Field, char **Player_Analysis, char CPU_Dk[] );

	char rs = 0,
		pd = 0,
		AB = 1;
	char vh = 0; 
	char CPU_Score = 0,
		Player_Score = 0;

	while (CPU_Score < 19 && Player_Score < 19)
	{
		Setcolor_White;	
		while(1)
		{
			CPU_Score = Score( Computer_Analysis);
			Player_Score = Score(Analysis);
			if(!AB) break;

			for (char i = 0; i < 10; i++) 
				if (CPU_Dk[i]==0) 
				{
					CPU_Dk[i]=99;
					AB = 1;
					Mark_Ships( Analysis, 2 );
					break;
				}

				system("cls");
				Show_Field ( Player_Field, Analysis, 9, 9, 1 );

				Show_Score (CPU_Score,Player_Score );

				AB = Player_Shot( Computer_Field, Analysis, CPU_Dk );

				if(AB) 
				{
					Setcolor_White;
					Player_Score++;
					system("cls");
					Show_Field ( Player_Field, Analysis, 9, 9, 1 );
					Show_Score (CPU_Score,Player_Score );
					Position.X = 25; Position.Y = 27; 
					Setcolor_Green;
					SetConsoleCursorPosition(hConsole, Position); cout<<"Стреляем еще раз"; Sleep(1000);
				}
		}


		while(1)
		{
			if(!rs) 
				rs = Random_Shot (Computer_Analysis, Player_Field, Player_Dk);

			if(!rs) {AB = 1;break;} 

			else
			{

				if (!vh && !pd)
				{


					AB = 0;
					system("cls");
					Show_Field ( Player_Field, Analysis, 9, 9, 1 );
					Show_Score (CPU_Score,Player_Score );
					Position.X = 25;
					Position.Y = 27; 
					Setcolor_Red;
					SetConsoleCursorPosition(hConsole, Position);
					cout<<"Компьютер обнаружил корабль";
					Sleep(1000);
					Setcolor_White;
				}
			}

			for (char i = 0; i < 10; i++) 
				if (Player_Dk[i]==0) 
				{
					Player_Dk[i]=5;
					rs = vh = 0;
					Mark_Ships( Computer_Analysis, 2 );
					AB = 0; break;
				}

				system("cls");
				Show_Field ( Player_Field, Analysis, 9, 9, 1 ); 

				if(!vh) 
					vh = Blind_Marked_Shot (Computer_Analysis, Player_Field, Player_Dk,0,0);

				if(!vh) {
					AB = 1;
					break;
				}

				if(vh) 
				{
					if (!pd)
					{

						AB = 0;
						system("cls");
						Show_Field ( Player_Field, Analysis, 9, 9, 1 ); Show_Score (CPU_Score,Player_Score );
						Position.X = 25; Position.Y = 27; 
						Setcolor_Red;
						SetConsoleCursorPosition(hConsole, Position); cout<<"Компьютер попал и стреляет еще раз!";
						Setcolor_White;
					}
				}

				for (char i = 0; i < 10; i++) 
					if (Player_Dk[i]==0) 
					{
						Player_Dk[i]=5; rs = vh = 0; Mark_Ships( Computer_Analysis, 2 ); AB = 0; break;
					}

					//

					pd = Predicted_Marked_Shot (Computer_Analysis, Player_Field, vh, Player_Dk);
					if(!pd) {AB = 1;break;} 

					if(pd) 
					{

						AB = 0;
						system("cls");
						Show_Field ( Player_Field, Analysis, 9, 9, 1 ); Show_Score (CPU_Score,Player_Score );
						Position.X = 25; Position.Y = 27; 
						Setcolor_Red;
						SetConsoleCursorPosition(hConsole, Position); cout<<"Компьютер попал и стреляет еще раз!"; Sleep(1000);
						Setcolor_White;
					}

					for (char i = 0; i < 10; i++) 
						if (Player_Dk[i]==0) 
						{
							Player_Dk[i]=99; rs = vh = 0; Mark_Ships( Computer_Analysis, 2 ); AB = 0; break;
						}

						system("cls");
						Show_Field ( Player_Field, Analysis, 9, 9, 1 );
		}
	}
	system("cls");
	cout<<"Игра завершена со счетом "<<int(CPU_Score)<<':'<<int(Player_Score)<<" в пользу "; (CPU_Score > Player_Score) ? cout<<"компьютера" : cout<<"пользователя\n\n\n";

}
