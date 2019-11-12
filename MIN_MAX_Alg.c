#include "FuncDeclare.h"

// ������ ��ǥ�� ���� �� ���� ū ���� ��ȯ == �̱� Ȯ���� ���� ��ǥ
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

// ������ ��ǥ�� ���� �� ���� ���� ���� ��ȯ == �̱� Ȯ���� ���� ���� ��ǥ
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

//��ǻ�Ͱ� �ּ��� ���� ã�� �� �ֵ��� �Լ�
int minMax(int Board[][A_SIZE], int Player, int* depth)
{
	int emptyCellList[A_SIZE * A_SIZE];
	int emptyCellCount = 0;
	int bestPosition = 0;
	int scoreList[A_SIZE * A_SIZE];
	int bestScore;

	bestScore = isAWin(Board, COMP);  // ��ǻ���� ��,��,�� Ȯ���ؼ� �ش��ϴ� ���� bestScore�� ����

	if (bestScore) //bestScore�� �����̹Ƿ� 0�� �ƴϸ� true, ��ǻ�Ͱ� �¸� �Ǵ� �й� ���� ���� return
	{
		return bestScore - *depth;
	}

	for (int i = 0;i < A_SIZE;i++)
	{
		for (int j = 0; j < A_SIZE; j++)
		{
			if (Board[i][j] == EMPTY)
				emptyCellList[emptyCellCount++] = i * A_SIZE + j;
		}
	}

	int CurPosition;
	for (int i = 0;i < emptyCellCount;i++)
	{
		CurPosition = emptyCellList[i];
		makeMove(Board, CurPosition / A_SIZE, CurPosition % A_SIZE, Player);

		(*depth)++;
		scoreList[i] = minMax(Board, !Player, depth);
		(*depth)--;

		makeMove(Board, CurPosition / A_SIZE, CurPosition % A_SIZE, EMPTY);
	}

	if (Player == COMP)
	{
		// ��ǻ�� ������ ���� ��ǻ���� �ּ��� ���� ã�� ���� max�Լ� ȣ��
		bestScore = max(scoreList, emptyCellCount, emptyCellList, &bestPosition);
	}

	if (Player == HUMAN)
	{
		// ���(�����)���忡���� ��ǻ�Ͱ� �ּ��� ���� ���� �ȵǴ� min�Լ� ȣ��
		bestScore = min(scoreList, emptyCellCount, emptyCellList, &bestPosition);
	}

	if (*depth != 0) // ��Ͱ� ���� ������ �ʾҴٸ� bestScore ��ȯ
	{
		return bestScore;
	}
	else //��Ͱ� �������� �ּ��� ��ġ�� ��ȯ �ؾߵǹǷ� bestMove ��ȯ
	{
		return bestPosition;
	}
}