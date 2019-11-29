/*
 * ���ϸ� : TTTFunc.c
 * ��� : ƽ���� ��� ���� �Լ� ����
 * ���� ��¥ : 2019-11-25
 * ���� ������ : �������б�
 *				���¼ҽ�����[Pro.�幮��] - Team5 (������, ���μ�, ������, ����)
 */

#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include "basedef.h"
#include "FuncDeclare.h"

 /*
 -��� : �Է� ���� �ʱ�ȭ
 */
void clear_stdin() {
	int ch;
	while ((ch = getchar()) != EOF && ch != '\n') {};
}

/*
-��� : �Է°��� ������ ��ġ���� �˻�
-��ȯ : �Է°��� 0���� ũ�� A_SIZE���� ������� �� ��ȯ
		�� �� �Է°��� ���� ��ȯ
*/
int validPosition(const int Board[][A_SIZE], int inputCol, int inputRow)
{
	if (0 > inputCol || inputCol >= A_SIZE)
		return FALSE;
	if (0 > inputRow || inputRow >= A_SIZE)
		return FALSE;
	if (Board[inputCol][inputRow] != EMPTY)
		return FALSE;

	return TRUE;
}

/*
- ��� : �ܼ�â �۾��� ��� ����
*/
void consoleClear(void)
{
	system("cls");
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
void printBoard(const int Board[][A_SIZE])
{
	int widthHeight = 6;


	char X[6][7] = { {"X    X"},{" X  X "},{"  XX  "},{"  XX  "} ,{" X  X "} ,{"X    X"} };
	char O[6][7] = { {" OOOO "},{"OO  OO"},{"O    O"} ,{"O    O"},{"OO  OO"} ,{" OOOO "} };
	char nothing[6][7] = { {"      "},{"      "},{" ==== "},{" ==== "},{"      "},{"      "} };

	consoleClear();



	printf_s("\n               BOARD\n\n");
	printf_s("     0        1        2\n\n");
	printf_s("    ---------------------------\n");

	for (int i = 0; i < A_SIZE; i++)
	{
		for (int l = 0; l < widthHeight; l++)
		{
			if (l == 0)
			{
				printf_s(" %d  |", i);
			}
			else
			{
				printf_s("    |");
			}

			for (int j = 0; j < A_SIZE; j++)
			{
				int status = Board[i][j];

				for (int k = 0; k < widthHeight; k++)
				{
					if (status == 0)
					{
						printf_s("%c", O[l][k]);
					}
					else if (status == 1)
					{
						printf_s("%c", X[l][k]);
					}
					else
					{
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
-��� : ���� ���Ұ� �� �������� �Ҵ�� ������ �ִ��� Ȯ���ϴ� ���
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
-���� :  �밢�� ��ġ	���� ��ġ	���� ��ġ	 ����ġ
	    ������ܿ���
	   	 �����ϴ�
		  O O X      O O O		 O X O		 O X O
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
			if (Board[i][j] == Player) //����
			{
				rowCount++;
			}
			if (Board[j][i] == Player) //����
			{
				columnCnt++;
			}
			if (i == j)
			{
				if (Board[i][j] == Player) // ���� ��ܿ��� ���� �ϴ������� �밢��
					downDiagonalCnt++;
			}

			if (i + j + 1 == A_SIZE)
			{
				if (Board[i][j] == Player) // ������ܿ��� �����ϴ������� �밢��
				{
					upDiagonalCnt++;
				}
			}
		}

		if (rowCount == A_SIZE || columnCnt == A_SIZE || downDiagonalCnt == A_SIZE || upDiagonalCnt == A_SIZE)
		{
			return TRUE;
		}
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
	int bestPos = 0;
	int col, row;

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
	col = bestPos / A_SIZE;
	row = bestPos % A_SIZE;
	makeMove(Board, col, row, Player);
}

/*
-��� : ����� ���� �Է� �ް� �÷��̾��� �ɺ��� ��ġ�ϴ� ���� ���忡 �Է�
		��� VS ��ǻ��, ��� VS ����� ��⿡ ���
*/
void HumanTurn(int Board[][A_SIZE], const int player)
{
	printf_s("\n��ġ�� �Է����ּ��� : ");
	int inputCol = -1, inputRow =-1;
	while (1)
	{
		scanf_s("%d %d", &inputCol, &inputRow);

		if (validPosition(Board, inputCol, inputRow))
		{
			break;
		}
		else
		{
			clear_stdin();
			printf_s("��ġ�� �ٽ� �Է����ּ��� : ");
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


	printTitle();
	printf_s("\n\t\t   *****���̵�!!*****\n");
	printf_s("\t\t   *     1. �ʱ�    *\n");
	printf_s("\t\t   *     2. �߱�    *\n");
	printf_s("\t\t   *     3. ���    *\n");
	printf_s("\t\t   ******************\n\n");
	printf_s("���̵��� �Է����ּ��� : ");


	while (level == 0)
	{
		scanf_s("%d", &level);


		if (level < 1 || level>3)

		{
			printf("���̵��� �ٽ� �Է����ּ��� : ");
			level = 0;
		}
		clear_stdin();
	}

	consoleClear();

	return level;
}

/*
-��� : ��� VS ��ǻ�� ���
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
		char choice;
		scanf_s("%c", &choice, sizeof(char));

		if (choice == 'O')
		{
			Player = HUMAN;
			break;
		}
		else if (choice == 'X')
		{
			Player = COMP;
			break;
		}
		else
		{
			printf_s("Choose correct symbols\n");
		}
		clear_stdin();
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


/*
-��� : ��� VS ��� ���
*/
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

void printTitle(void)
{
	printf_s("\n\n");
	printf_s("  #####  #   ###    #####   #     ###     #####  ###   #####\n");
	printf_s("    #       #         #    # #   #          #   #   #  #    \n");
	printf_s("    #    #  #         #   #####  #          #   #   #  ###  \n");
	printf_s("    #    #  #         #   #   #  #          #   #   #  #    \n");
	printf_s("    #    #   ###      #   #   #   ###       #    ###   #####\n\n");

	printf_s("                ###    #    ##   ##  #####\n");
	printf_s("               #      # #   #  #  #  #    \n");
	printf_s("               # ##  #####  #  #  #  ###  \n");
	printf_s("               #  #  #   #  #  #  #  #    \n");
	printf_s("                ###  #   #  #     #  #####\n\n");
}

/*
-��� : �ʱ� �޴� ȭ���� ���
*/
void showMenu()
{
	int choice = 0;
	
	printTitle();

	printf_s("\t\t ��带 ������ �ּ���.\n\n");
	printf_s("\t\t 1. Player VS Player\n");
	printf_s("\t\t 2. Player VS Computer\n\n");

	while (!(choice == 1 || choice == 2)) // choice�� 1�Ǵ� 2�� �ƴ϶��
	{
		if (!(choice == 1 || choice == 2))
		{
			printf_s("1�Ǵ� 2�� �������ּ���! : ");
		}
		scanf_s("%d", &choice);
		clear_stdin();
	}

	consoleClear();

	if (choice == 1)
	{
		runGameVSHuman();
	}
	else // choice = 2
	{
		runGameVSCom();
	}
}