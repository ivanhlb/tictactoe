#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <time.h>       /* time */

using namespace std;
int state = 1, turn = -1;
char playerSymbol = ' ', aiSymbol = ' ';
char board[3][3] =
{
	{ ' ', ' ', ' ' },
	{ ' ', ' ', ' ' },
	{ ' ', ' ', ' ' }
};
char horizontalBorder[5] =	{ '-','+','-','+','-' };
#pragma region Methods
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
	system("pause");
	system("CLS");
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
	//board is 5 x 5 including borders
	for (int i = 0; i < 5; ++i)	//rows
	{

		for (int j = 0; j < 5; ++j)	//items in rows
		{
			if (i % 2 == 1)
			{
				cout << horizontalBorder[j];
			}
			else
			{
				if (j % 2 == 1)	//draw border on 1 and 3
				{
					cout << '|';
				}
				else
				{
					cout << board[i / 2][j / 2];	// i = 0 - 4	//board only has 0-2
				}
			}
		};
		cout << endl;
	}
	system("pause");
	system("CLS");
}
void checkState()
{
	char winnerSymbol = ' ';
	if (board[1][1] != ' ')//check diagonals
	{
		if (board[0][0] == board[1][1] && board[1][1] == board[2][2])	//element 0,0 2,2 and 4,4	//diagonal 1
		{
			winnerSymbol = board[1][1];
		}
		if (board[0][2] == board[1][1] && board[1][1] == board[2][0])	//element 4,0 2,2 and 0,4	//diagonal 2
		{
			winnerSymbol = board[1][1];
		}
	}
	for (int i = 0; i < sizeof(board) / sizeof(board[0]); ++i)
	{

		if (board[i][0] == board[i][1] && board[i][1] == board[i][2])	//checks rows
		{
			winnerSymbol = board[i][0];
		}
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i])	//checks columns
		{
			winnerSymbol = board[0][i];
		}
		if (winnerSymbol != ' ')
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
			return;
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
	system("pause");
	system("CLS");

	cout << "you put piece on " << spot << endl;
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
	return (num - 1) / 3;
}
int getCol(int num)
{
	return (num % 3 == 0) ? 2 : num % 3 - 1;
}
int exit()
{
	cout << "Press any key to exit..." << endl;
	_getch();	//system("pause");	//for windows only
	return 0;
}
#pragma endregion

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
		checkState();
		drawBoard();
	}
	exit();
}