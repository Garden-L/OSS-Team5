﻿#include <stdio.h>

#define Size 3

#define FALSE 0
#define TRUE 1

#define WIN 10
#define LOSE -10
#define DRAW 0

enum { O, X, EMPTY };
int HUMAN = 0;
int COMP = 1;

//보드 내부의 모든 원소를 EMPTY로 초기화
void initBoard(int Board[][Size])
{
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			Board[i][j] = EMPTY;
		}
	}
}

// 보드판 출력
void printBoard(const int Board[][Size])
{
	char symbol[] = { 'O','X','-' };

	printf_s("\n  BOARD\n\n");

	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			printf_s("%c ", symbol[Board[i][j]]);
		}
		printf("\n");
	}

	printf_s("\n\n");
}

//보드가 다 찼는지의 유무를 반환
int isBoardFull(const int Board[][Size]) 
{
	for (int i = 0;i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			if (Board[i][j] == EMPTY)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

// 플레이어가 선택한 곳을 보드에 기입
void makeMove(int Board[][Size], int Col, int Row, const int Player) 
{
	Board[Col][Row] = Player; 
}


/*
연속된 3개의 플레이어 심볼 확인
일치 : 1(TRUE) 반환
불일치 : 0(FLASE) 반환
*/
int is3inARow(const int Board[][Size], const int Player) 
{
	int rowCount = 0;
	int columnCnt = 0;
	int downDiagonalCnt = 0;
	int upDiagonalCnt = 0;
	
	for (int i = 0; i < Size; i++)
	{
		rowCount = 0;
		columnCnt = 0;

		for (int j = 0; j < Size; j++)
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

			if (i + j + 1 == Size)
			{
				if (Board[i][j] == Player)
				{
					upDiagonalCnt++;
				}
			}
		}
		if (rowCount == Size || columnCnt == Size || downDiagonalCnt == Size || upDiagonalCnt == Size)
			return TRUE;
	}

	return FALSE;
}

/*
자신이 이길경우 10점
상대방이 이길경우 -10점
비길경우 0점
*/
int isAWin(const int Board[][Size], const int Player) 
{
	if (is3inARow(Board, Player)) // 이기는 경우
	{
		return WIN;
	}

	if (is3inARow(Board, !Player)) // 상대방이 이기는 경우
	{
		return LOSE;
	}

	return DRAW; // 비기는 경우
}

// 최적의 좌표의 점수 중 가장 큰 값을 반환 == 이길 확률이 높은 좌표
int max(int scoreList[], int emptyCellCount, int emptyCellList[], int* bestMove)
{
	if (!emptyCellCount)
	{
		return 0;
	}

	int max = -20;

	for (int i = 0;i < emptyCellCount;i++)
	{
		if (scoreList[i] > max)
		{
			max = scoreList[i];
			*bestMove = emptyCellList[i];
		}
	}
	return max;
}

// 최적의 좌표의 점수 중 가장 작은 값을 반환 == 이길 확률이 가장 낮은 좌표
int min(int scoreList[], int emptyCellCount, int emptyCellList[], int* bestMove)
{
	if (!emptyCellCount)
	{
		return 0;
	}

	int min = +20;

	for (int i = 0;i < emptyCellCount;i++)
	{
		if (scoreList[i] < min) 
		{
			min = scoreList[i];
			*bestMove = emptyCellList[i];
		}
	}
	return min;
}

//컴퓨터가 최선의 수를 찾을 수 있도록 함수
int minMax(int Board[][Size], int Player, int* depth) 
{
	int emptyCellList[Size*Size];
	int emptyCellCount = 0;
	int bestPosition = 0;
	int scoreList[Size* Size];
	int bestScore;

	bestScore = isAWin(Board, COMP);  // 컴퓨터의 승,무,패 확인해서 해당하는 값을 bestScore에 넣음
	
	if (bestScore) //bestScore가 정수이므로 0이 아니면 true, 컴퓨터가 승리 또는 패배 했을 때만 return
	{
		return bestScore - *depth;
	}

	for (int i = 0;i < Size;i++)
	{
		for (int j = 0; j < Size; j++)
		{
			if (Board[i][j] == EMPTY)
				emptyCellList[emptyCellCount++] = i * Size + j; 
		}
	}

	int CurPosition;
	for (int i = 0;i < emptyCellCount;i++)
	{
		CurPosition = emptyCellList[i];
		makeMove(Board, CurPosition /Size, CurPosition % Size, Player);

		(*depth)++;
		scoreList[i] = minMax(Board, !Player, depth);
		(*depth)--;

		makeMove(Board, CurPosition / Size, CurPosition % Size, EMPTY);
	}

	if (Player == COMP) 
	{
		// 컴퓨터 차례일 때는 컴퓨터의 최선의 수를 찾기 위해 max함수 호출
		bestScore = max(scoreList, emptyCellCount, emptyCellList, &bestPosition);
	}

	if (Player == HUMAN) 
	{
		// 사람(사용자)입장에서는 컴퓨터가 최선의 수를 내면 안되니 min함수 호출
		bestScore = min(scoreList, emptyCellCount, emptyCellList, &bestPosition);
	}

	if (*depth != 0) // 재귀가 아직 끝나지 않았다면 bestScore 반환
	{
		return bestScore;
	}
	else //재귀가 끝났으면 최선의 위치를 반환 해야되므로 bestMove 반환
	{
		return bestPosition;
	}
}

// 컴퓨터 차례
void ComputerTurn(int Board[][Size], int Player) 
{
	int depth = 0;
	int bestPos = minMax(Board, Player, &depth); // 최선의 위치 선택
	printf_s("Searched.... bestMove: %d\n", bestPos + 1);
	makeMove(Board, bestPos/Size, bestPos%Size, COMP);
}

//사람 차례
void HumanTurn(int Board[][Size]) 
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

//게임 실행
void runGame(void)
{
	printf_s("\nChoose X or O. O moves first !!\n\n");
	while (1) 
	{

		char choice;
		scanf_s("%c", &choice, sizeof(char));

		getchar();

		if (choice == 'O') 
		{
			HUMAN = O;
			COMP = X;
			break;
		}

		if (choice == 'X') 
		{
			HUMAN = X;
			COMP = O;
			break;
		}
		else 
		{
			printf_s("Choose correct symbols\n");
		}
	}

	int gameOver = 0;
	int Player = O;
	int Board[Size][Size];

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

int main(void) 
{
	runGame();

	return 0;
}