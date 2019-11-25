/*
 * ���ϸ� : MIN_MAX_Alg.c
 * ��� : �θƽ� �˰��� ���� �Լ� ����
 * ���� ��¥ : 2019-11-25
 * ���� ������ : �������б�
 *				���¼ҽ�����[Pro.�幮��] - Team5 (������, ���μ�, ������, ����)
 */

#include "FuncDeclare.h"
#include <stdlib.h>
#include <time.h>

/*
-��ȯ : �̱�Ȯ���� ���� ������ ��ǥ���� ��ȯ�Ѵ�.
-�Ű����� : scoreList�� �� ��ǥ�� ���� ������ ������ �迭�̴�.
			bestMove�� ������ ��ǥ�� ���� �ε����� ����Ų��.
*/
int Max(int scoreList[], int emptyCellCount, int emptyCellList[], int* bestMove)
{
	if (!emptyCellCount)
	{
		return 0;
	}

	int max = -20;

	for (int i = 0; i < emptyCellCount; i++)
	{
		if (scoreList[i] > max)
		{
			max = scoreList[i];
			*bestMove = emptyCellList[i];
		}
	}
	return max;
}

/*
-��ȯ : �̱�Ȯ���� ���� ������ ��ǥ���� ��ȯ�Ѵ�.
-�Ű����� : scoreList�� �� ��ǥ�� ���� ������ ������ �迭�̴�.
			bestMove�� ������ ��ǥ�� ���� �ε����� ����Ų��.
*/
int Min(int scoreList[], int emptyCellCount, int emptyCellList[], int* bestMove)
{
	if (!emptyCellCount)
	{
		return 0;
	}

	int min = +20;

	for (int i = 0; i < emptyCellCount; i++)
	{
		if (scoreList[i] < min)
		{
			min = scoreList[i];
			*bestMove = emptyCellList[i];
		}
	}
	return min;
}

/*
-��� : ��ǻ���� ���ʰ� �Ǹ� ���� ��ġ�ϴ� ��޳��̵� �Լ�
-�Ű����� : depth�� �Լ��� ��������� ����ɶ��� ���Ƚ���� �����Ѵ�.
-��ȯ : ��ǻ�Ͱ� ��ġ�� ���� �ε����� ��ȯ�Ѵ�.
-�帧 : ������ ��ĭ�� ���� ������ �����Ͽ� ��������� ����� ��ǻ���� ���� ��ġ�ϴ� ������ �ݺ� �����Ѵ�.
		��Ͱ� ���̻� ����� �� ������ �ּ��� ��ġ���� ��ȯ�� �� ���带 �����·� ������Ų��.
*/
int minMax_HARD(int Board[][A_SIZE], int Player, int* depth)
{
	int emptyCellList[A_SIZE * A_SIZE];
	int emptyCellCount = 0;
	int bestPosition = 0;
	int scoreList[A_SIZE * A_SIZE];
	int bestScore;

	bestScore = isAWin(Board, COMP);

	if (bestScore)
	{
		return bestScore - *depth;
	}

	for (int i = 0; i < A_SIZE; i++)
	{
		for (int j = 0; j < A_SIZE; j++)
		{
			if (Board[i][j] == EMPTY)
				emptyCellList[emptyCellCount++] = i * A_SIZE + j;
		}
	}

	int CurPosition;
	for (int i = 0; i < emptyCellCount; i++)
	{
		CurPosition = emptyCellList[i];
		makeMove(Board, CurPosition / A_SIZE, CurPosition % A_SIZE, Player);

		(*depth)++;
		scoreList[i] = minMax_HARD(Board, !Player, depth);
		(*depth)--;

		makeMove(Board, CurPosition / A_SIZE, CurPosition % A_SIZE, EMPTY);
	}

	if (Player == COMP)
	{

		bestScore = Max(scoreList, emptyCellCount, emptyCellList, &bestPosition);
	}

	if (Player == HUMAN)
	{

		bestScore = Min(scoreList, emptyCellCount, emptyCellList, &bestPosition);
	}

	if (*depth != 0)
	{
		return bestScore;
	}
	else
	{
		return bestPosition;
	}
}


/*
-��� : ��ǻ���� ���ʰ� �Ǹ� ���� ��ġ�ϴ� �߱޳��̵� �Լ�
-�Ű����� : depth�� �Լ��� ��������� ����ɶ��� ���Ƚ���� �����Ѵ�.
-��ȯ : ��ǻ�Ͱ� ��ġ�� ���� �ε����� ��ȯ�Ѵ�.
-�帧 : ��޳��̵������� �帧�� ����������, ��ĭ�� �������� ���̵��� ���ߴ� ����� �۵��Ѵ�.
*/

int minMax_NORMAL(int Board[][A_SIZE], int Player, int* depth)
{
	int emptyCellList[A_SIZE * A_SIZE];
	int emptyCellCount = 0;
	int bestPosition = 0;
	int scoreList[A_SIZE * A_SIZE];
	int bestScore;

	bestScore = isAWin(Board, COMP);

	if (bestScore)
	{
		return bestScore - *depth;
	}

	for (int i = 0; i < A_SIZE; i++)
	{
		for (int j = 0; j < A_SIZE; j++)
		{
			if (Board[i][j] == EMPTY)
				emptyCellList[emptyCellCount++] = i * A_SIZE + j;
		}
	}

	if (emptyCellCount >= (A_SIZE*A_SIZE / 2))
	{
		int CurPosition;
		for (int i = 0; i < emptyCellCount; i++)
		{
			CurPosition = emptyCellList[i];
			makeMove(Board, CurPosition / A_SIZE, CurPosition % A_SIZE, Player);

			(*depth)++;
			scoreList[i] = minMax_NORMAL(Board, !Player, depth);
			(*depth)--;

			makeMove(Board, CurPosition / A_SIZE, CurPosition % A_SIZE, EMPTY);
		}

		if (Player == COMP)
		{
			bestScore = Max(scoreList, emptyCellCount, emptyCellList, &bestPosition);
		}

		if (Player == HUMAN)
		{
			bestScore = Min(scoreList, emptyCellCount, emptyCellList, &bestPosition);
		}
	}

	else

	{
		int CurPosition;
		for (int i = 0; i < emptyCellCount; i++)
		{
			CurPosition = emptyCellList[i];
			makeMove(Board, CurPosition / A_SIZE, CurPosition % A_SIZE, Player);

			(*depth)++;
			scoreList[i] = minMax_HARD(Board, !Player, depth);
			(*depth)--;

			makeMove(Board, CurPosition / A_SIZE, CurPosition % A_SIZE, EMPTY);
		}

		if (Player == COMP)
		{
			bestScore = Min(scoreList, emptyCellCount, emptyCellList, &bestPosition);

		}

		if (Player == HUMAN)
		{

			bestScore = Max(scoreList, emptyCellCount, emptyCellList, &bestPosition);
		}

	}

	if (*depth != 0)
	{
		return bestScore;
	}
	else
	{
		return bestPosition;
	}
}


/*
-��� : ��ǻ���� ���ʰ� �Ǹ� ������ ��ĭ�� Ȯ���Ͽ� ��ĭ �� ������ ĭ�� ���� ��ġ�ϴ� �ʱ޳��̵� �Լ�
-��ȯ : ��ǻ�Ͱ� ��ġ�� ���� �ε����� ��ȯ�Ѵ�.
*/
int minMax_EASY(int Board[][A_SIZE], int Player)
{
	int emptyCellList[A_SIZE * A_SIZE] = { 0 };
	int emptyCellCount = 0;
	int bestPosition;

	srand((int)time(NULL));


	for (int i = 0; i < A_SIZE; i++)
	{
		for (int j = 0; j < A_SIZE; j++)
		{
			if (Board[i][j] == EMPTY)
				emptyCellList[emptyCellCount++] = i * A_SIZE + j;
		}
	}

	bestPosition = rand() % emptyCellCount;

	return emptyCellList[bestPosition];
}





