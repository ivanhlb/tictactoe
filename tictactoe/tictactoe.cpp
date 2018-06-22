#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <time.h>       /* time */

#pragma region Forward Declaration
void getPlayerSymbol();
void rollTurn();
void drawBoard();
void checkState();
void AITurn();
void processTurn();
int rnd(int, int);
int getRow(int);
int getCol(int);
int exit();
#pragma endregion
using namespace std;
int state = 1, turn = -1;
char playerSymbol = ' ', aiSymbol = ' ';
char board[5][5] =
{
	{ ' ', '|', ' ', '|', ' ' },
{ '-','-','-','-','-' },
{ ' ', '|', ' ', '|', ' ' },
{ '-','-','-','-','-' },
{ ' ', '|', ' ', '|', ' ' }
};

int main()
{
	while (state == 1)
	{
		getPlayerSymbol();
		rollTurn();
		if (turn == 0)	//player turn
		{
			processTurn();
		}
		else if (turn == 1)	// AI turn
		{
			AITurn();
		}
		drawBoard();
	}
	exit();
}
void getPlayerSymbol()
{
	if (playerSymbol == 'x' || playerSymbol == 'o')
		return;
	cout << "enter 'x' or 'o' for your symbol." << endl;
	cin >> playerSymbol;
	while (playerSymbol != 'x' && playerSymbol != 'o')
	{
		cout << "Please enter valid symbol." << endl << flush;
		cin >> playerSymbol;
	}
	if (playerSymbol == 'x')
		aiSymbol = 'o';
	else if (playerSymbol == 'o')
		aiSymbol = 'x';
	else throw new exception("Undefined symbols!");
}
void rollTurn()
{
	if (turn != -1)
		return;
	cout << "deciding who to go first..." << endl;
	turn = rnd(0, 1);
	if (turn == 0)
		cout << "Player goes first." << endl;
	else if (turn == 1)
		cout << "AI goes first." << endl;
	else
		throw new exception("Undefined turn...");
}
void drawBoard()
{
	for (int i = 0; i < sizeof(board) / sizeof(board[0]); ++i)
	{
		for (char c : board[i])
		{
			cout << c;
		};
		cout << endl;
	}
}
void checkState()
{
	char winnerSymbol = ' ';
	if (board[2][2] != ' ')//check diagonals
	{
		if (board[0][0] == board[2][2] == board[4][4])	//element 0,0 2,2 and 4,4	//diagonal 1
		{
			winnerSymbol = board[2][2];
		}
		if (board[0][4] == board[2][2] == board[4][0])	//element 4,0 2,2 and 0,4	//diagonal 2
		{
			winnerSymbol = board[2][2];
		}
	}
	for (int i = 0; i < sizeof(board) / sizeof(board[0]); i += 2)
	{
		
		if (board[i][0] == board[i][2] == board[i][4])	//checks rows
		{
			winnerSymbol = board[i][0];
		}
		if (board[0][i] == board[2][i] == board[4][i])	//checks columns
		{
			winnerSymbol = board[0][i];
		}
		if(winnerSymbol != ' ')
		{
			//someone won... but who?
			if (winnerSymbol == playerSymbol)
			{
				cout << "Player wins!" << endl;
			}
			else if (winnerSymbol == aiSymbol)
			{
				cout << "AI wins!" << endl;
			}
			else throw new exception("Unidentified symbol!");
			state = 0;
		}
	}
}
void AITurn()
{
	int spot = rnd(1, 9);
	while (board[getRow(spot)][getCol(spot)] != ' ')
	{
		//cout << "Spot is occupied. " << endl;
		spot = rnd(1, 9);
	}
	board[getRow(spot)][getCol(spot)] = aiSymbol;
	cout << "AI put piece on " << spot << endl;
	checkState();
	turn = 0;
}
void processTurn()
{
	char spotChar = '0';
	int spot = 0;
	cout << "Enter a number from 1-9 to place a piece." << endl;
	cin >> spotChar;

numbCheck:
	while (spotChar - '1' > 8 || spotChar - '1' < 0)
	{
		cout << "Please enter a valid number." << endl;
		cin >> spotChar;
	}
	spot = spotChar - '0';
	if (board[getRow(spot)][getCol(spot)] != ' ')
	{
		cout << "Spot is occupied. ";
		spotChar = '0';
		goto numbCheck;
	}
	board[getRow(spot)][getCol(spot)] = playerSymbol;
	cout << "you put piece on " << spot << endl;
	checkState();
	turn = 1;
	//system("CLS");	//windows only....
}
int rnd(int min, int max)
{
	srand(time(NULL));
	return (rand() % (max - min)) + min;
}
int getRow(int num)
{
	return (num - 1) / 3 * 2;
}
int getCol(int num)
{
	return (num % 3 == 0) ? 4 : ((num % 3) - 1) * 2;
}
int exit()
{
	cout << "Press any key to exit..." << endl;
	_getch();	//system("pause");	//for windows only
	return 0;
}
