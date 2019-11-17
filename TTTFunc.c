#include <stdio.h>
#include "basedef.h"
#include "FuncDeclare.h"

//���� ������ ��� ���Ҹ� EMPTY�� �ʱ�ȭ
void initBoard(int Board[][A_SIZE])
{
	for (int i = 0; i < A_SIZE; i++)
	{
		for (int j = 0; j < A_SIZE; j++)
		{
			Board[i][j] = EMPTY;
		}
	}
}


// ������ ���
void printBoard(const int Board[][A_SIZE])
{
	char symbol[] = { 'O','X','-' };

	printf_s("\n  BOARD\n\n");

	for (int i = 0; i < A_SIZE; i++)
	{
		for (int j = 0; j < A_SIZE; j++)
		{
			printf_s("%c ", symbol[Board[i][j]]);
		}
		printf("\n");
	}

	printf_s("\n\n");
}



//���尡 �� á������ ������ ��ȯ
int isBoardFull(const int Board[][A_SIZE])
{
	for (int i = 0;i < A_SIZE; i++)
	{
		for (int j = 0; j < A_SIZE; j++)
		{
			if (Board[i][j] == EMPTY)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}



// �÷��̾ ������ ���� ���忡 ����
void makeMove(int Board[][A_SIZE], int Col, int Row, const int Player)
{
	Board[Col][Row] = Player;
}


/*
���ӵ� 3���� �÷��̾� �ɺ� Ȯ��
��ġ : 1(TRUE) ��ȯ
����ġ : 0(FLASE) ��ȯ
*/
int is3inARow(const int Board[][A_SIZE], const int Player)
{
	int rowCount = 0;
	int columnCnt = 0;
	int downDiagonalCnt = 0;
	int upDiagonalCnt = 0;

	for (int i = 0; i < A_SIZE; i++)
	{
		rowCount = 0;
		columnCnt = 0;

		for (int j = 0; j < A_SIZE; j++)
		{
			if (Board[i][j] == Player)
			{
				rowCount++;
			}
			if (Board[j][i] == Player)
			{
				columnCnt++;
			}
			if (i == j)
			{
				if (Board[i][j] == Player)
					downDiagonalCnt++;
			}

			if (i + j + 1 == A_SIZE)
			{
				if (Board[i][j] == Player)
				{
					upDiagonalCnt++;
				}
			}
		}
		if (rowCount == A_SIZE || columnCnt == A_SIZE || downDiagonalCnt == A_SIZE || upDiagonalCnt == A_SIZE)
			return TRUE;
	}

	return FALSE;
}

/*
�ڽ��� �̱��� 10��
������ �̱��� -10��
����� 0��
*/
int isAWin(const int Board[][A_SIZE], const int Player)
{
	if (is3inARow(Board, Player)) // �̱�� ���
	{
		return WIN;
	}

	if (is3inARow(Board, !Player)) // ������ �̱�� ���
	{
		return LOSE;
	}

	return DRAW; // ���� ���
}



// ��ǻ�� ����
void ComputerTurn(int Board[][A_SIZE], int Player , int level)
{
	int depth = 0;
	int bestPos;

	switch (level)
	{
	case 1:
		bestPos = minMax_EASY(Board, Player); // �ּ��� ��ġ ����
		break;

	case 2:
		bestPos = minMax_NORMAL(Board, Player, &depth); // �ּ��� ��ġ ����
		break;

	case 3:
		bestPos= minMax_HARD(Board, Player, &depth); // �ּ��� ��ġ ����
		break;

	default:
		printf("System Error\n");
		bestPos = ERROR;
		break;
	}


	printf_s("Searched.... bestMove: %d\n", bestPos + 1);
	makeMove(Board, bestPos / A_SIZE, bestPos % A_SIZE, COMP);
}

//��� ����
void HumanTurn(int Board[][A_SIZE])
{
	printf_s("\nEnter your move !!\n\n");
	int inputCol, inputRow;
	while (1)
	{
		scanf_s("%d %d", &inputCol, &inputRow);
		if (Board[inputCol][inputRow] == EMPTY)
		{
			break;
		}
		else
		{
			printf_s("try again : ");
		}
	}
	makeMove(Board, inputCol, inputRow, HUMAN);
}



//���� ����
void runGame(void)
{
	int Player = 0;
	int level;

	while (1)
	{
		
		printf_s("\nChoose your level!!\n| 1 | 2 | 3 |\n");
		scanf_s("%d", &level);
		
		if (level >= 1 && level <= 3)
		{
			break;
		}

		else
		{
			printf("Choose correct level\n");
		}
	}
	printf_s("\nChoose X or O. O moves first !!\n\n");
	while (1)
	{
		getchar();
		char choice;
		scanf_s("%c", &choice, sizeof(char));

		getchar();

		if (choice == 'O')
		{
			Player = HUMAN;

			break;
		}

		if (choice == 'X')
		{
			Player = COMP;
			break;
		}
		else
		{
			printf_s("Choose correct symbols\n");
		}
	}

	int gameOver = 0;
	int Board[A_SIZE][A_SIZE];

	initBoard(Board);
	printBoard(Board);

	while (!gameOver)
	{

		if (Player == HUMAN)
		{
			HumanTurn(Board);
		}
		else
		{
			ComputerTurn(Board, Player,level);
		}

		printBoard(Board);

		if (is3inARow(Board, Player))
		{
			printf_s("Game Over\n");
			gameOver = 1;
			if (Player == COMP)
			{
				printf_s("Computer Wins\n");
			}
			else
			{
				printf_s("Human Wins\n");
			}
		}

		if (isBoardFull(Board))
		{
			printf_s("Game Over\n");
			gameOver = 1;
			printf_s("It's a Draw\n");
		}

		Player = !Player;
	}
}