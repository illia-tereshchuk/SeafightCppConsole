#include <iostream>
#include <ctime>
#include <windows.h>
using namespace std;

bool Random_Shot (char **Analysis, char **Player, char Player_Dk[])
{
	char y = rand()%10,
		x = rand()%10;
	while (Analysis[y][x]) //Выбор неразведанной координаты
	{
		y = rand()%10;
		x = rand()%10;
	};

	if (Player[y][x] >= 10 && Player[y][x] <= 40)
	{
		switch(Player[y][x])
		{
		case 40: Player_Dk[0]--; break;
		case 31: Player_Dk[1]--; break;
		case 30: Player_Dk[2]--; break;
		case 22: Player_Dk[3]--; break;
		case 21: Player_Dk[4]--; break; 
		case 20: Player_Dk[5]--; break;
		case 13: Player_Dk[6]--; break; 
		case 12: Player_Dk[7]--; break; 
		case 11: Player_Dk[8]--; break;
		case 10: Player_Dk[9]--;
		}
		//1 в массиве обозначает поврежденный участок корабля
		Player[y][x] = Analysis[y][x] = 1; 
		//5 в массиве - ближайшие к поврежденной точки
		if (y < 9 && Analysis[y+1][x]==0) Analysis[y+1][x] = 5;
		if (y > 0 && Analysis[y-1][x]==0) Analysis[y-1][x] = 5;
		if (x < 9 && Analysis[y][x+1]==0) Analysis[y][x+1] = 5;
		if (x > 0 && Analysis[y][x-1]==0) Analysis[y][x-1] = 5;
		//Значение 1 означает попадание компьютера
		return 1;
	}
	else
	{	
		//2 в массиве обозначает простреленный пустой участок
		Player[y][x] = Analysis[y][x] = 2;
		//0 - компьютер промахнулся
		return 0;
	}
}

char Blind_Marked_Shot (char **Analysis, char **Player, char Player_Dk[], char i, char j)
{
	for (char y = 0; y < 10; y++)
	{
		for (char x = 0; x < 10; x++)
			if (Analysis[y][x]==5) {
				i = y;
				j = x;
				break;
			}
	}
	cout<<Player[i][j];
	if (Player[i][j] >= 10 && Player[i][j] <= 40)
	{
		switch(Player[i][j])
		{
		case 40: Player_Dk[0]--; break; case 31: Player_Dk[1]--; break; case 30: Player_Dk[2]--; break;
		case 22: Player_Dk[3]--; break; case 21: Player_Dk[4]--; break; case 20: Player_Dk[5]--; break;
		case 13: Player_Dk[6]--; break; case 12: Player_Dk[7]--; break; case 11: Player_Dk[8]--; break;
		case 10: Player_Dk[9]--; break;
		}
		
		Player[i][j] = Analysis[i][j] = 1; 

		if (i < 9 && Analysis[i+1][j]==0) Analysis[i+1][j] = 5;
		if (i > 0 && Analysis[i-1][j]==0) Analysis[i-1][j] = 5;
		if (j < 9 && Analysis[i][j+1]==0) Analysis[i][j+1] = 5;
		if (j > 0 && Analysis[i][j-1]==0) Analysis[i][j-1] = 5;
		

		if (i < 9 && Analysis[i+1][j]==1) return 'V';
		if (i > 0 && Analysis[i-1][j]==1) return 'V';
		if (j < 9 && Analysis[i][j+1]==1) return 'H';
		if (j > 0 && Analysis[i][j-1]==1) return 'H';
	}					

	else
	{	
		Player[i][j] = Analysis[i][j] = 2;
		return 0;
	}
}


bool Predicted_Marked_Shot (char **Analysis, char **Player, char Hor_or_Vert, char Player_Dk[])
{
	for (char i = 0; i < 10; i++)
	{
		for (char j = 0; j < 10; j++)
		{
			if (Analysis[i][j]==5) 
			{
				switch (Hor_or_Vert)
				{
				case 'H': if (i < 9 && Analysis[i+1][j]==1) Analysis[i][j]=2;
					if (i > 0 && Analysis[i-1][j]==1) Analysis[i][j]=2; break;

				case 'V': if (j > 0 && Analysis[i][j-1]==1) Analysis[i][j]=2;
					if (j < 9 && Analysis[i][j+1]==1) Analysis[i][j]=2; break;
				}
			}
		}
	}

	int m=0,
		p=0;
	bool Out = 0;

	for (char i = 0; i < 10; i++)
	{
		if(Out) break;
		for (char j = 0; j < 10; j++)
		{
			if(Out) break;
			if (Analysis[i][j]==5) 
			{
				m = i;
				p = j;
				Out = 1;
				break;
			}
		}
	}

	if (Player[m][p] >= 10 && Player[m][p] <= 40)
	{
		switch(Player[m][p])
		{
		case 40: Player_Dk[0]--; break; case 31: Player_Dk[1]--; break; case 30: Player_Dk[2]--; break;
		case 22: Player_Dk[3]--; break; case 21: Player_Dk[4]--; break; case 20: Player_Dk[5]--; break;
		case 13: Player_Dk[6]--; break; case 12: Player_Dk[7]--; break; case 11: Player_Dk[8]--; break;
		case 10: Player_Dk[9]--; break;
		}

		switch(Hor_or_Vert)
		{
		case 'H':
			Player[m][p] = Analysis[m][p] = 1; 
			if (p < 9 && Analysis[m][p+1]==0) Analysis[m][p+1] = 5;
			if (p > 0 && Analysis[m][p-1]==0) Analysis[m][p-1] = 5;
			break;

		case 'V':
			Player[m][p] = Analysis[m][p] = 1; 
			if (p < 9 && Analysis[m+1][p]==0) Analysis[m][p+1] = 5;
			if (p > 0 && Analysis[m-1][p]==0) Analysis[m][p-1] = 5;
			break;
		}
		return 1;
	}

	else
	{	
		Player[m][p] = Analysis[m][p] = 2;
		return 0;
	}
}