#include "FuncDeclare.h"
#include <stdlib.h>
#include <time.h>

// ������ ��ǥ�� ���� �� ���� ū ���� ��ȯ == �̱� Ȯ���� ���� ��ǥ
int Max(int scoreList[], int emptyCellCount, int emptyCellList[], int* bestMove)
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
int Min(int scoreList[], int emptyCellCount, int emptyCellList[], int* bestMove)
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

//��ǻ�Ͱ� �ּ��� ���� ã�� �� �ֵ��� �Լ� ���̵�
int minMax_HARD(int Board[][A_SIZE], int Player, int* depth)
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
		scoreList[i] = minMax_HARD(Board, !Player, depth);
		(*depth)--;

		makeMove(Board, CurPosition / A_SIZE, CurPosition % A_SIZE, EMPTY);
	}

	if (Player == COMP)
	{
		// ��ǻ�� ������ ���� ��ǻ���� �ּ��� ���� ã�� ���� max�Լ� ȣ��
		bestScore = Max(scoreList, emptyCellCount, emptyCellList, &bestPosition);
	}

	if (Player == HUMAN)
	{
		// ���(�����)���忡���� ��ǻ�Ͱ� �ּ��� ���� ���� �ȵǴ� min�Լ� ȣ��
		bestScore = Min(scoreList, emptyCellCount, emptyCellList, &bestPosition);
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

//��ǻ�Ͱ� �ּ��� ���� ã�� �� �ֵ��� �Լ� �� ���̵�
int minMax_NORMAL(int Board[][A_SIZE], int Player, int* depth)
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
			// ��ǻ�� ������ ���� ��ǻ���� �ּ��� ���� ã�� ���� max�Լ� ȣ��
			bestScore = Max(scoreList, emptyCellCount, emptyCellList, &bestPosition);
		}

		if (Player == HUMAN)
		{
			// ���(�����)���忡���� ��ǻ�Ͱ� �ּ��� ���� ���� �ȵǴ� min�Լ� ȣ��
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
			// ��ǻ�Ͱ� �̻��� ���� ���� �����ν����ڰ� �¸��� ���ɼ��� �÷��ش�.
			bestScore = Min(scoreList, emptyCellCount, emptyCellList, &bestPosition);

		}

		if (Player == HUMAN)
		{

			bestScore = Max(scoreList, emptyCellCount, emptyCellList, &bestPosition);
		}

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

//��ǻ�Ͱ� �ּ��� ���� ã�� �� �ֵ��� �Լ� �ϳ��̵�
int minMax_EASY(int Board[][A_SIZE], int Player)
{
	int emptyCellList[A_SIZE * A_SIZE];
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





