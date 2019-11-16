#include <stdio.h>
#include <time.h>
#include "basedef.h"
#include "FuncDeclare.h"

void rankingPrint() {

	FILE *fp = NULL;

	char symbol[2] = { 'W','D' };
	char name[255];
	double time;
	int status;


	fp = fopen_s(&fp, "log.txt", "r");

	if (fp == NULL) { printf_s("NO RANKING\n"); }
	else {
		while (feof(fp) != EOF) {
			fscanf_s("%f %d %s", &time, &status, name);
			printf_s("%c %f %s\n", symbol[status - 1], time, name);
		}
		fclose(fp);
	}


}

void rankingInsert(double time, int status) {

	char name[255];
	FILE *fp = NULL;


	if (status == 0) {
		//���Ÿ� �ƹ��͵� ���� ����
	}
	else if (status == 1) {
		//�̰�����


		printf_s("\ntime = %0.0f\n", time);
		printf_s("insert name : ");
		scanf_s("%s", name);

	}
	else if (status == 2) {
		//�������
	}
	else {
		printf_s("ERROR");
	}

}

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
void printBoard(int Board[][A_SIZE])
{
	int widthHeight = 6;
	char X[6][6] = { {"X    X"},{" X  X "},{"  XX  "},{"  XX  "} ,{" X  X "} ,{"X    X"} };
	char O[6][6] = { {" OOOO "},{"OO  OO"},{"O    O"} ,{"O    O"},{"OO  OO"} ,{" OOOO "} };
	char nothing[6][6] = { {"      "},{"      "},{" ==== "},{" ==== "},{"      "},{"      "} };


	printf_s("\n               BOARD\n\n");
	printf_s("     1        2        3\n\n");
	printf_s("    ---------------------------\n");

	for (int i = 0; i < A_SIZE; i++)
	{
		for (int l = 0; l < widthHeight; l++)
		{
			if (l == 0) { printf_s(" %d  |", i + 1); }
			else { printf_s("    |"); }

			for (int j = 0; j < A_SIZE; j++)
			{
				int status = Board[i][j];

				for (int k = 0; k < widthHeight; k++) {
					if (status == 0) {
						printf_s("%c", O[l][k]);
					}
					else if (status == 1) {
						printf_s("%c", X[l][k]);
					}
					else {
						printf_s("%c", nothing[l][k]);
					}
				}
				printf_s(" | ");
			}
			printf_s("\n");
		}
		printf_s("    ---------------------------\n");
	}

	printf_s("\n\n");
}

//���尡 �� á������ ������ ��ȯ
int isBoardFull(const int Board[][A_SIZE])
{
	for (int i = 0; i < A_SIZE; i++)
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
void ComputerTurn(int Board[][A_SIZE], int Player)
{
	int depth = 0;
	int bestPos = minMax(Board, Player, &depth); // �ּ��� ��ġ ����
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

	rankingPrint();

	printf_s("\nChoose X or O. O moves first !!\n\n");
	while (1)
	{

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
	int startTime;
	int endTime;
	int status = -1;

	initBoard(Board);
	printBoard(Board);

	//��ŷ �ð� ����
	startTime = clock();

	while (!gameOver)
	{

		if (Player == HUMAN)
		{
			HumanTurn(Board);
		}
		else
		{
			ComputerTurn(Board, Player);
		}

		printBoard(Board);

		if (is3inARow(Board, Player))
		{
			printf_s("Game Over\n");
			gameOver = 1;
			if (Player == COMP)
			{
				printf_s("Computer Wins\n");
				status = 0;
			}
			else
			{
				printf_s("Human Wins\n");
				status = 1;
			}
		}

		if (isBoardFull(Board))
		{
			printf_s("Game Over\n");
			gameOver = 1;
			printf_s("It's a Draw\n");
			status = 2;
		}

		Player = !Player;
	}

	//��ŷ �ð� ��
	endTime = clock();

	rankingInsert((endTime - startTime) / CLOCKS_PER_SEC, status);
}