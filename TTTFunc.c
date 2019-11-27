#include <stdio.h>
#include <time.h>
#include "basedef.h"
#include "FuncDeclare.h"


void printRanking(void) {
	//��ŷ ������ ����
	/*�ð� ��/���� �̸�\n*/
	struct ranking r[5];

	FILE *rankingFile = NULL;

	fopen_s(&rankingFile, "rank.txt", "r");


	//init
	for (int i = 0; i < 5; i++)
	{
		r[i].id = -1;
		r[i].score = -1;
		r[i].status = -1;
	}



	if (rankingFile != NULL)
	{

		for (int i = 0; i < 5; i++)
		{
			if (feof(rankingFile) == EOF) { break; }
			fscanf_s(rankingFile, "%f %d %d\n", &r[i].score, &r[i].status, &r[i].id);
		}

		fclose(rankingFile);
	}
	else
	{
		fopen_s(&rankingFile, "rank.txt", "w");
		fclose(rankingFile);
	}

	/*score status name*/
	printf_s("\nNow Ranking\nScore(time)\tStatus\t\tStudent ID\n");
	for (int i = 0; i < 5; i++)
	{
		char status = '\0';
		if (r[i].score == -1) { break; }

		if (r[i].status == WIN)
		{
			status = 'W';
		}
		else
		{
			status = 'D';
		}

		printf_s("%.2f\t\t%c\t\t%d\n", r[i].score, status, r[i].id);
	}

	printf_s("\n\n");

}

int insertRanking(float time, int status) {

	if (status == LOSE) { return 0; }

	/*�ð� ��/���� �̸�\n*/
	struct ranking r[5];

	//init
	for (int i = 0; i < 5; i++)
	{
		r[i].score = -1;
		r[i].status = -1;
		r[i].id = -1;
	}

	int seat = -1;
	int id = -1;
	FILE *rankingFile = NULL;

	fopen_s(&rankingFile, "rank.txt", "r");

	if (rankingFile != NULL)
	{
		for (int i = 0; i < 5; i++)
		{
			if (feof(rankingFile) == EOF) { break; }
			fscanf_s(rankingFile, "%f %d %d\n", &r[i].score, &r[i].status, &r[i].id);
		}
		fclose(rankingFile);
	}


	for (int i = 0; i < 5; i++)
	{
		if (r[i].score == -1)
		{
			seat = i;
			break;
		}

		if (r[i].score > time)
		{
			seat = i;
			break;
		}
	}

	if (seat == -1)
	{
		printf_s("Your score is not good enough to rank. Play the game faster\n\n");
	}
	else
	{

		printf_s("Your score is %.2f\n\n", time);
		printf_s("Scores can be ranked. Please enter your student ID\nID(To int) : ");
		scanf_s("%d", &id);
		printf_s("\n\n");

		for (int i = 4; i > seat; i--)
		{
			r[i].id = r[i - 1].id;
			r[i].score = r[i - 1].score;
			r[i].status = r[i - 1].status;
		}

		r[seat].score = time;
		r[seat].id = id;
		r[seat].status = status;

		fopen_s(&rankingFile, "rank.txt", "w");

		for (int i = 0; i < 5; i++)
		{
			if (r[i].score == -1) { break; }
			fprintf_s(rankingFile, "%.2f %d %d\n", r[i].score, r[i].status, r[i].id);
		}

		fclose(rankingFile);
	}

	printf_s("Well saved!\n\n");

	return 0;
}

/*
- ��� : ������ �ʱ�ȭ �Լ�
- ���� : Board[i][j] = EMPTY, 0 <= i <= A_SIZE, 0 <= j <= A_SIZE
�ʱ�ȭ �� �迭�� ��� (#define EMPTY 0)
0 0 0
0 0 0
0 0 0

*/
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


/*
- ��� : ��ü ������ ��� (3x3)
�� ���ҿ� ������ �ɺ� ������ ��ȭ�Ͽ� ����Ѵ�.
- ��ȯ : void
- ��¿���:    �� ĭ ���		O�Է� ĭ ���			X�Է� ĭ ���
--------		 ----------			 ----------
|      |		 |  OOOO  |			 | X    X |
|      |		 | OO  OO |			 |  X  X  |
| ==== |		 | O    O |			 |   XX   |
| ==== |		 | O    O |			 |   XX   |
|      |		 | OO  OO |			 |  X  X  |
|      |		 |  OOOO  |			 | X    X |
--------		 ----------			 ----------
*/
void printBoard(int Board[][A_SIZE])
{
	int widthHeight = 6;

	char X[6][6] = { {"X    X"},{" X  X "},{"  XX  "},{"  XX  "} ,{" X  X "} ,{"X    X"} };
	char O[6][6] = { {" OOOO "},{"OO  OO"},{"O    O"} ,{"O    O"},{"OO  OO"} ,{" OOOO "} };
	char nothing[6][6] = { {"      "},{"      "},{" ==== "},{" ==== "},{"      "},{"      "} };

	system("cls");


	printf_s("\n               BOARD\n\n");
	printf_s("     0        1        2\n\n");
	printf_s("    ---------------------------\n");

	for (int i = 0; i < A_SIZE; i++)
	{
		for (int l = 0; l < widthHeight; l++)
		{



			if (l == 0) { printf_s(" %d  |", i); }


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



/*
-��� : ���� ���Ұ� �� �������� �Ҵ�� ���� �ִ��� Ȯ���ϴ� ���
�� ������ ���� ���� ��� ���ʰ� �������
�� ������ ���� ���� ���� ��Ⱑ �ȳ��� ���
-��ȯ : ���� ������ �� á�� ��� - TURE,   �� ���� ������ ���� ��� - FALSE
*/
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



/*
-��� : �÷��̾ �Է��� ��ġ�� �� �÷��̾��� �ɺ��� �Է�
-����:
���� - input : (1,2), playerSimbol : 'O', �̶� 'O'�� �������� 1�̶� ����
��� - ���� �ε���1,�ε���2 ��ġ�� O�� �Ҵ�� ���� �� ����, Board[1][2] = 1
*/
void makeMove(int Board[][A_SIZE], int Col, int Row, const int Player)
{
	Board[Col][Row] = Player;
}


/*
-��� : ����, ����, �밢������ 3���� ������ �ɺ��� Ȯ��
-��ȯ : 3���� ���������� ������ �� : TRUE,  �ҿ����� �� : FALSE
-���� : �밢�� ��ġ	���� ��ġ	���� ��ġ	 ����ġ

O O X 		 O O O		 O X O		 O X O
O X O		 O X X		 X X O		 X O O
X O X		 X O X		 O X X		 O X X

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
-��� : �ڽ��� ���� ���ο� ���� �Ҵ�� ���� ���� ��ȯ
-��ȯ :
�ڽ��� �̱� ��� - 10�� (WIN)
������ �̱� ��� - 10�� (LOSE)
��� ��� - 0 (DRAW)

���� :		  �̱� ���				   		  �� ���				     	  ��� ���
(�� �÷��̾��� �ɺ��� O�� ����)	 (�� �÷��̾��� �ɺ��� X�� ����)    (�� �÷��̾��� �ɺ��� X�� ����)
O O O				  		   O O O				  		   O X O
O X X				  		   O X X				  		   O X X
X O X 				  		   X O X 				  		   X O X

WIN(10) ��ȯ				  LOSE(-10) ��ȯ			   			 DRAW(0) ��ȯ
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




/*
-��� : ��ǻ�Ͱ� ���� �δ� ���
��� VS ��ǻ�� ����� ��� ���
*/

void ComputerTurn(int Board[][A_SIZE], int Player, int level)
{
	int depth = 0;
	int bestPos;

	switch (level)
	{
	case 1:
		bestPos = minMax_EASY(Board, Player);				//�ʱ޸�� ����
		break;

	case 2:
		bestPos = minMax_NORMAL(Board, Player, &depth);		//�߱޸�� ����
		break;

	case 3:
		bestPos = minMax_HARD(Board, Player, &depth);		//��޸�� ����
		break;

	default:
		printf("System Error\n");
		bestPos = ERROR;
		break;
	}
	makeMove(Board, bestPos / A_SIZE, bestPos%A_SIZE, Player);


}




/*
-��� : ����� ���� �Է� �ް� �÷��̾��� �ɺ��� ��ġ�ϴ� ���� ���忡 �Է�
��� VS ��ǻ��, ��� VS ����� ��⿡ ���
*/
void HumanTurn(int Board[][A_SIZE], const int player)
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
	makeMove(Board, inputCol, inputRow, player);
}




/*
-��� : ���̵��� �����ϴ� ȭ���� ����Ѵ�.
-��ȯ : ����ڰ� ������ ��ǻ���� ���̵��� ��ȯ�Ѵ�.
*/
int computerLvlSelect(void)
{

	int level = 0;

	while (level == 0)
	{

		printf("\t���̵��� �������ּ���!!\n");
		printf("\t      1. �ʱ�\n");
		printf("\t      2. �߱�\n");
		printf("\t      2. ���\n");
		scanf_s("%d", &level);


		if (level < 1 || level>3)


		{
			printf("Choose correct level\n");
			level = 0;
		}
	}

	return level;
}

/*
-��� : ����� ���� �Է� �ް� �÷��̾��� �ɺ��� ��ġ�ϴ� ���� ���忡 �Է�
��� VS ��ǻ��, ��� VS ����� ��⿡ ���
*/
void runGameVSCom(void)
{
	int Player = 0;
	int level = computerLvlSelect();


	//����Ʈ ��ŷ
	printRanking();


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
			HumanTurn(Board, Player);
		}
		else
		{
			ComputerTurn(Board, Player, level);
		}

		printBoard(Board);

		if (is3inARow(Board, Player))
		{
			printf_s("Game Over\n");
			gameOver = 1;
			if (Player == COMP)
			{
				status = LOSE;
				printf_s("Computer Wins\n");
			}
			else
			{
				status = WIN;
				printf_s("Human Wins\n");
			}
		}

		if (isBoardFull(Board))
		{
			printf_s("Game Over\n");
			gameOver = 1;
			status = DRAW;
			printf_s("It's a Draw\n");
		}

		Player = !Player;
	}

	//��ŷ �ð� ��
	endTime = clock();
	insertRanking((float)(endTime - startTime) / CLOCKS_PER_SEC, status);
}


//��� VS ��� ����� ���
void runGameVSHuman(void)
{
	int Player = 0;

	int gameOver = 0;
	int Board[A_SIZE][A_SIZE];

	initBoard(Board);
	printBoard(Board);

	while (!gameOver)
	{

		if (Player == HUMAN)
		{
			//Player1�� ����
			printf_s("Player1�� �����Դϴ�.\n");
			HumanTurn(Board, Player);
		}
		else
		{
			//Player2�� ����
			printf_s("Player2�� �����Դϴ�.\n");
			HumanTurn(Board, Player);
		}

		printBoard(Board);

		if (is3inARow(Board, Player))
		{
			printf_s("Game Over\n");
			gameOver = 1;
			if (Player == COMP)
			{
				printf_s("Player2 Wins\n");
			}
			else
			{
				printf_s("Player1 Wins\n");
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


/*
-��� : �ʱ� �޴� ȭ���� ���
*/
void showMenu()
{
	printf("\n\n\n\t\tTicTacToe Game\n\n");
	printf("\t     ��带 ������ �ּ���.\n\n");
	printf("\t      1. Player VS Player\n");
	printf("\t      2. Player VS Computer\n");

	int choice;
	scanf_s("%d", &choice);
	getchar();

	while (!(choice == 1 || choice == 2)) { // choice�� 1�Ǵ� 2�� �ƴ϶��
		printf("1�Ǵ� 2�� �������ּ���!\n");
		scanf_s("%d", &choice);
		getchar();
	}

	if (choice == 1)
	{
		runGameVSHuman();
	}
	else // choice = 2
		runGameVSCom();
}